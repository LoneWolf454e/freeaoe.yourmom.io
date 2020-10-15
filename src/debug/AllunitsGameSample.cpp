/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "AllunitsGameSample.h"

#include <vector>

#include "core/Logger.h"
#include "core/Types.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitFactory.h"
#include "mechanics/UnitManager.h"
#include "mechanics/Map.h"
#include "mechanics/Player.h"

void AllunitsGameSample::setupMap()
{
    map_->setupAllunitsMap();
}

void AllunitsGameSample::setupActors(const ResourceMap &startingResources)
{
    m_gaiaPlayer = std::make_shared<Player>(UnitManager::GaiaID, UnitManager::GaiaID, startingResources);
    m_humanPlayer = std::make_shared<Player>(1, 1, startingResources);
    m_enemyPlayer = std::make_shared<Player>(2, 2, startingResources);
}

void AllunitsGameSample::setupUnits()
{
    addHumanTownCenter();
    addHumanUnits();
    addEnemyBuildings();
    addEnemyUnits();
}

std::shared_ptr<Player> AllunitsGameSample::getGaiaPlayer()
{
    return m_gaiaPlayer;
}

std::shared_ptr<Player> AllunitsGameSample::getHumanPlayer()
{
    return m_humanPlayer;
}

std::shared_ptr<Player> AllunitsGameSample::getEnemyPlayer()
{
    return m_enemyPlayer;
}

void AllunitsGameSample::addHumanTownCenter()
{
    Unit::Ptr unit = UnitFactory::Inst().createUnit(Unit::TownCenter, m_humanPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*2, 48*2, 0));
}

void AllunitsGameSample::addHumanUnits()
{
    const int dx = 115;
    const int dy = 115;
    const int baseX = dx * 2;
    const int baseY = dy * 3;

    std::vector<int> units{4, 7, 74, 280, 279, 358, 440, 725, 751, 765};

    int pos = 0;

    for (const int unitID : units) {
        int x = (pos % 5) * dx + baseX;
        int y = (pos / 5) * dy + baseY;

        WARN << "::::: createUnit" << unitID;
        Unit::Ptr unit = UnitFactory::createUnit(unitID, m_humanPlayer, *unitManager_);
        unitManager_->add(unit, MapPos(x, y, 0));

        pos++;
    }
}

void AllunitsGameSample::addEnemyUnits()
{
    Unit::Ptr unit;

    unit = UnitFactory::createUnit(74, m_enemyPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*12, 48*20, 0));
    unit = UnitFactory::createUnit(74, m_enemyPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*11, 48*20, 0));

    unit = UnitFactory::createUnit(358, m_enemyPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*9, 48*20, 0));
}

void AllunitsGameSample::addEnemyBuildings()
{
    Unit::Ptr unit = UnitFactory::createUnit(Unit::Dock, m_enemyPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*15, 48*20, 0));
}
