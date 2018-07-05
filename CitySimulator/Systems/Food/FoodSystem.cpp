#include "FoodSystem.hpp"
#include "FoodRule.hpp"
#include "Food.hpp"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"


class FoodRule;
const int FoodSystem::OPERATING_COST;
FoodSystem::FoodSystem() : BaseSystem(FOOD)
{
    FoodRule::breakfastTime = helper::Time(10,0);
    FoodRule::lunchTime = helper::Time(14,0);
    FoodRule::dinnerTime = helper::Time(120,0);
}

FoodSystem::~FoodSystem() = default;

/**
 * \brief Registers a new food plot in the system
 * \param plot Plot to be registered
 */
int FoodSystem::Register(Plot* plot)
{
    (*plot).Register(new Food(plot));
    BaseSystem::Register(plot);
    return 0;
}

/**
 * \brief Updates food system. Tally scores for food plots
 */
void FoodSystem::Update()
{
}

/**
 * \brief Logs a citizen being satisified with a food
 * \param citizen Citzen being logged
 * \param rule Rule being logged
 */
void FoodSystem::LogSatisfied(Citizen* citizen, BaseRule* rule)
{
    // Dynamic cast rule to create a snapshot copy 
    const auto log = new Log(citizen->Coords(), new FoodRule(*dynamic_cast<FoodRule*>(rule)), citizen);
    satisfiedLog.InsertLast(log);
}

/**
 * \brief Logs a citizen being unsatisified with a food
 * \param citizen Citzen being logged
 * \param rule Rule being logged
 */
void FoodSystem::LogUnsatisfied(Citizen* citizen, BaseRule* rule)
{
    // Dynamic cast rule to create a snapshot copy 
    const auto log = new Log(citizen->Coords(), new FoodRule(*dynamic_cast<FoodRule*>(rule)), citizen);
    unsatisfiedLog.InsertLast(log);
}

float FoodSystem::GetSatisfaction() const
{
    const float overloadedPenalty = 0.05f;
    float overloadedTally = 0;
    float earnedMoney = 0;
    for (auto&& plot : plots)
    {
        const auto food = dynamic_cast<Food*>(plot->GetPlotType());
        // If earnings exceeded operating costs, additional money is only worth half the score
        earnedMoney += food->earnedMoney - (food->earnedMoney - Clamp(food->earnedMoney, 0, OPERATING_COST)) * 0.5f;
        overloadedTally += food->overloadedTally;
    }
    earnedMoney /= plots.Count();
    float satisfaction = 1.f - float(OPERATING_COST - earnedMoney) / float(OPERATING_COST);
    
    overloadedTally = overloadedTally / plots.Count() * overloadedPenalty;
    satisfaction -= overloadedTally;
    
    satisfaction = Clamp(satisfaction, 0.f, 1.f);
    return satisfaction;
}

