#include "FoodSystem.hpp"
#include "FoodRule.hpp"
#include "Food.hpp"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"


class FoodRule;

FoodSystem::FoodSystem() : BaseSystem(FOOD)
{}

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
    for (auto && plot : plots)
    {
        // Tallying and adding score for occupant count. Positive for within limit people, negative for over
        const auto count = plot->GetOccupantCount();
        score += (std::min(count, maxOccupantCount) * scorePerOccupant - std::max(count - maxOccupantCount, 0) * overPenalty) * CoreController::Instance()->GetDeltaTime();
    }
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
    const float overloadedPenalty = 0.01f;
    const int dailyCustomer = 50;
    float overloadedTally = 0;
    float customerTally = 0;
    for (auto&& plot : plots)
    {
        const auto food = dynamic_cast<Food*>(plot->GetPlotType());
        customerTally += food->customerCountTally - (food->customerCountTally - Clamp(food->customerCountTally, 0, dailyCustomer)) * 0.5f;
        overloadedTally += food->overloadedTally;
    }
    customerTally /= plots.Count();
    float satisfaction = 1.f - float(dailyCustomer - customerTally) / float(dailyCustomer);
    
    overloadedTally = overloadedTally / plots.Count() * overloadedPenalty;
    satisfaction -= overloadedTally;
    
    satisfaction = Clamp(satisfaction, 0.f, 1.f);
    return satisfaction;
}

