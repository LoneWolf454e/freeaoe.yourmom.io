#pragma once

#include "actions/IAction.h"

#include <memory>
#include <deque>
#include <unordered_set>

using ActionPtr = std::shared_ptr<IAction>;

struct UnitActionHandler
{
    UnitActionHandler(Unit *unit);

    std::unordered_set<Task> availableActions() noexcept;

    Task findMatchingTask(const genie::ActionType &type, int targetUnit) noexcept;

    bool hasAutoTargets() const noexcept { return !m_autoTargetTasks.empty(); }
    void checkForAutoTargets() noexcept;

    int taskGraphicId(const genie::ActionType taskType, const IAction::UnitState state);

    void prependAction(const ActionPtr &action) noexcept;
    void queueAction(const ActionPtr &action) noexcept;
    void removeAction(const ActionPtr &action);
    void clearActionQueue() noexcept;

    void setCurrentAction(const ActionPtr &action) noexcept;
    const ActionPtr &currentAction() const noexcept { return m_currentAction; }

    ActionPtr m_currentAction;
    std::deque<ActionPtr> m_actionQueue;

    std::unordered_set<Task> m_autoTargetTasks;

private:
    Unit *m_unit;
};