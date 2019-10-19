#include "gen/enums.h"

#include "ScriptLoader.h"

#include "ScriptTokenizer.h"
#include "grammar.gen.tab.hpp"
#include "core/Logger.h"
#include "EnumLogDefs.h"
#include "conditions/Conditions.h"

namespace ai {

int ScriptLoader::parse(std::istream& in, std::ostream& out) {

    ScriptTokenizer scanner {*this};
    ScriptParser parser {*this, scanner};
    //parser.set_debug_stream(out);
    //parser.set_debug_level(4);

    int res = parser.parse();

    return res;
}


std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type)
{
    switch(type) {
    case Fact::Trueval:
        return std::make_shared<Conditions::ConstantCondition>(true);
    case Fact::Falseval:
        return std::make_shared<Conditions::ConstantCondition>(false);
    default:
        WARN << "unimplemented condition" << type;
        break;
    }

    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Age building)
{
    WARN << "unimplemented condition" << type << building;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Building building)
{
    WARN << "unimplemented condition" << type << building;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Building building, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << building << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Civ civ)
{
    WARN << "unimplemented condition" << type << civ;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Commodity commodity)
{
    WARN << "unimplemented condition" << type << commodity;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Commodity commodity, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << commodity << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const MapSizeType mapsize)
{
    WARN << "unimplemented condition" << type << mapsize;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const MapTypeName maptype)
{
    WARN << "unimplemented condition" << type << maptype;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber)
{
    WARN << "unimplemented condition" << type << playerNumber;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const Building building, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << building << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const Civ civ)
{
    WARN << "unimplemented condition" << type << playerNumber << civ;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const Commodity commodity, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << commodity << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const DiplomaticStance stance)
{
    WARN << "unimplemented condition" << type << playerNumber << stance;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const Age age)
{
    WARN << "unimplemented condition" << type << playerNumber << comparison << age;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const Unit unit, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << unit << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const RelOp comparison, const Age age)
{
    WARN << "unimplemented condition" << type << comparison << age;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const RelOp comparison, const DifficultyLevel level)
{
    WARN << "unimplemented condition" << type << comparison << level;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const RelOp comparison, const StartingResourcesType startingResources)
{
    WARN << "unimplemented condition" << type << comparison << startingResources;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const StrategicNumberName strategicNumber, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << strategicNumber << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Unit unit, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << unit << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const int number1, const RelOp comparison, const int number2)
{
    WARN << "unimplemented condition" << type << number1 << comparison << number2;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const int number1, const int number2)
{
    WARN << "unimplemented condition" << type << number1 << number2;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const int number, const WallType wallType)
{
    WARN << "unimplemented condition" << type << number << wallType;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const int number)
{
    WARN << "unimplemented condition" << type << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const ResearchItem research)
{
    WARN << "unimplemented condition" << type << research;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Unit unit)
{
    WARN << "unimplemented condition" << type << unit;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const VictoryConditionName condition)
{
    WARN << "unimplemented condition" << type << condition;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createOrCondition(std::shared_ptr<Condition> &condition1, std::shared_ptr<Condition> &condition2)
{
    return std::make_shared<Conditions::OrCondition>(condition1, condition2);
}

std::shared_ptr<Condition> ScriptLoader::createNotCondition(const RelOp type, std::shared_ptr<Condition> &condition)
{
    WARN << "unimplemented not condition" << type;
    return nullptr;
}

////////////// actions

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type)
{
    WARN << "unimplemented action" << type;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const std::string &string)
{
    WARN << "unimplemented action" << type << string;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const int number1, const int number2)
{
    WARN << "unimplemented action" << type << number1 << number2;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const int number)
{
    WARN << "unimplemented action" << type << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const int number, const WallType wallType)
{
    WARN << "unimplemented action" << type << number << wallType;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Age age)
{
    WARN << "unimplemented action" << type << age;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Building building)
{
    WARN << "unimplemented action" << type << building;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const ResearchItem research)
{
    WARN << "unimplemented action" << type << research;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Commodity commodity)
{
    WARN << "unimplemented action" << type << commodity;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Unit unit)
{
    WARN << "unimplemented action" << type << unit;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Commodity commodity, const int number)
{
    WARN << "unimplemented action" << type << commodity << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const int number)
{
    WARN << "unimplemented action" << type << playernumber << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const StrategicNumberName strategicNumber, const int number)
{
    WARN << "unimplemented action" << type << strategicNumber << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const Commodity commodity, const int number)
{
    WARN << "unimplemented action" << type << playernumber << commodity << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const std::string &string)
{
    WARN << "unimplemented action" << type << playernumber << string;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const DiplomaticStance stance)
{
    WARN << "unimplemented action" << type << playernumber << stance;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const Commodity commodity)
{
    WARN << "unimplemented action" << type << playernumber << commodity;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const DifficultyParameter difficulty, const int number)
{
    WARN << "unimplemented action" << type << difficulty << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const int number1, const int number2)
{
    WARN << "unimplemented action" << type << playernumber << number1 << number2;
    return nullptr;
}

Condition::~Condition() { }

} // namespace ai
