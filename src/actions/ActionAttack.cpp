#include "ActionAttack.h"

#include "ActionMove.h"
#include "core/Constants.h"
#include "core/Logger.h"
#include "mechanics/Civilization.h"
#include "mechanics/Missile.h"
#include "mechanics/Player.h"
#include "mechanics/UnitManager.h"

#include <genie/Types.h>
#include <genie/dat/Unit.h>
#include <genie/dat/unit/Combat.h>
#include <genie/dat/unit/Creatable.h>

#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

ActionAttack::ActionAttack(const Unit::Ptr &attacker, const Task &task) :
    IAction(IAction::Type::Attack, attacker, task),
    m_targetUnit(task.target)
{
    Unit::Ptr target = task.target.lock();
    if (!target) {
        WARN << "target gone";
        return;
    }
    m_targetPosition = target->position();
    if (target->playerId() == attacker->playerId()) {
        m_targetUnit.reset();
    }
}

ActionAttack::ActionAttack(const Unit::Ptr &attacker, const MapPos &targetPos, const Task &task) :
    IAction(IAction::Type::Attack, attacker, task),
    m_targetPosition(targetPos),
    m_attackGround(true)
{
}

IAction::UnitState ActionAttack::unitState() const
{
    if (m_firing) {
        return IAction::UnitState::Attacking;
    } else {
        return IAction::UnitState::Idle;
    }
}

IAction::UpdateResult ActionAttack::update(Time time)
{
    Unit::Ptr unit = m_unit.lock();
    if (!unit) {
        return IAction::UpdateResult::Completed;
    }

    Unit::Ptr targetUnit = m_targetUnit.lock();
    if (!targetUnit && !m_attackGround) {
        DBG << "Target unit gone";
        return IAction::UpdateResult::Completed;
    }

    if (targetUnit) {
        m_targetPosition = targetUnit->position();
    }

    const float distance = (targetUnit ?
                unit->distanceTo(targetUnit) :
                unit->distanceTo(m_targetPosition)
                                )
            / Constants::TILE_SIZE;

    if (distance > unit->data()->Combat.MaxRange) {
        if (!unit->data()->Speed) {
            DBG << "this unit can't move...";
            return IAction::UpdateResult::Failed;
        }

        std::shared_ptr<ActionMove> moveAction = ActionMove::moveUnitTo(unit, targetUnit);

        moveAction->maxDistance = unit->data()->Combat.MaxRange * Constants::TILE_SIZE;
        unit->actions.prependAction(moveAction);

        return IAction::UpdateResult::NotUpdated;
    }

    const float minDistance = unit->data()->Combat.MinRange * Constants::TILE_SIZE;
    if (minDistance > 0.f && m_targetPosition.distance(unit->position()) < minDistance) {
        if (!unit->data()->Speed) {
            DBG << "this unit can't move...";
            return IAction::UpdateResult::Failed;
        }

        if (!unit->actions.findAnyTask(genie::ActionType::RetreatToShootingRage, -1).data) {
            return IAction::UpdateResult::Failed;
        }

        const float angleToTarget = unit->position().angleTo(m_targetPosition);

        float targetX = m_targetPosition.x + cos(angleToTarget + M_PI) * minDistance;
        float targetY = m_targetPosition.y + sin(angleToTarget + M_PI) * minDistance;

        std::shared_ptr<ActionMove> moveAction = ActionMove::moveUnitTo(unit, MapPos(targetX, targetY), m_task);
        unit->actions.prependAction(moveAction);
        return IAction::UpdateResult::NotUpdated;
    }

    if (unitFiresMissiles(unit) && missilesUnitCanFire(unit) <= 0) {
        return IAction::UpdateResult::NotUpdated;
    }

    ScreenPos screenPosition = unit->position().toScreen();
    ScreenPos targetScreenPosition = m_targetPosition.toScreen();
    unit->setAngle(screenPosition.angleTo(targetScreenPosition));

    float timeSinceLastAttack = (time - m_lastAttackTime) * 0.0015;

    if (timeSinceLastAttack < unit->data()->Combat.DisplayedReloadTime) {
        m_firing = true;
    } else {
        m_firing = false;
    }

    if (timeSinceLastAttack < unit->data()->Combat.ReloadTime) {
        return IAction::UpdateResult::NotUpdated;
    }

    if (targetUnit && targetUnit->healthLeft() <= 0.f) {
        return IAction::UpdateResult::Completed;
    }
    m_lastAttackTime = time;

    // TODO: Create a flare here owned by the owner of the targeted unit, to show where the attack is coming from

    if (unit->data()->Creatable.SecondaryProjectileUnit != -1) { // I think we should prefer the secondary, for some reason, at least those are cooler
        spawnMissiles(unit, unit->data()->Creatable.SecondaryProjectileUnit, m_targetPosition, targetUnit);
        return IAction::UpdateResult::Updated;
    } else if (unit->data()->Combat.ProjectileUnitID != -1) {
        spawnMissiles(unit, unit->data()->Combat.ProjectileUnitID,  m_targetPosition, targetUnit);
        return IAction::UpdateResult::Updated;
    } else {
        for (const genie::unit::AttackOrArmor &attack : unit->data()->Combat.Attacks) {
            targetUnit->takeDamage(attack, 1.); // todo: damage multiplier
        }
    }

    return IAction::UpdateResult::Updated;
}

void ActionAttack::spawnMissiles(const Unit::Ptr &source, const int unitId, const MapPos &target, const Unit::Ptr &targetUnit)
{
    DBG << "Spawning missile" << unitId;

    const std::array<float, 3> &graphicDisplacement = source->data()->Combat.GraphicDisplacement;
    const std::array<float, 3> &spawnArea = source->data()->Creatable.ProjectileSpawningArea;
    DBG << source->data()->Combat.AccuracyPercent << source->data()->Creatable.SecondaryProjectileUnit;

    Player::Ptr owner = source->player().lock();
    if (!owner) {
        WARN << "no owning player";
        return;
    }
    const genie::Unit &gunit = owner->civilization.unitData(unitId);

    float widthDispersion = 0.;
    if (source->data()->Creatable.TotalProjectiles > 1) {
        widthDispersion = spawnArea[0] * Constants::TILE_SIZE / source->data()->Creatable.TotalProjectiles;
    }
    for (int i=0; i<missilesUnitCanFire(source); i++) {
        MapPos individualTarget = target;
        individualTarget.x +=  -cos(source->angle()) * i*widthDispersion - spawnArea[0]/2.;
        individualTarget.y +=  sin(source->angle()) * i*widthDispersion - spawnArea[1]/2.;
        Missile::Ptr missile = std::make_shared<Missile>(gunit, source, individualTarget, targetUnit);
        missile->setMap(source->map());

        missile->setBlastType(Missile::BlastType(source->data()->Combat.BlastAttackLevel), source->data()->Combat.BlastWidth);

        float offsetX = graphicDisplacement[0];
        float offsetY = graphicDisplacement[1];

        MapPos pos = source->position();
        pos.x += -sin(source->angle()) * offsetX + cos(source->angle()) * offsetX;
        pos.y +=  cos(source->angle()) * offsetY + sin(source->angle()) * offsetY;
        pos.z += graphicDisplacement[2] * Constants::TILE_SIZE_HEIGHT;

        if (spawnArea[2] > 0) {
            pos.x += (rand() % int((100 - spawnArea[2]) * spawnArea[0] * Constants::TILE_SIZE)) / 100.;
            pos.y += (rand() % int((100 - spawnArea[2]) * spawnArea[1] * Constants::TILE_SIZE)) / 100.;
        }
        missile->setPosition(pos);
        source->unitManager().addMissile(missile);
    }
}

bool ActionAttack::unitFiresMissiles(const Unit::Ptr &unit)
{
    return (unit->data()->Creatable.SecondaryProjectileUnit != -1) || (unit->data()->Combat.ProjectileUnitID != -1);
}

int ActionAttack::missilesUnitCanFire(const Unit::Ptr &source)
{
    return std::min(int(source->data()->Creatable.TotalProjectiles), source->data()->Creatable.MaxTotalProjectiles - source->activeMissiles);
}
