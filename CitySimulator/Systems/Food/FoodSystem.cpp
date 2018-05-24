#include "FoodSystem.h"
#include "Food.h"
#include "FoodRule.h"
#include "../../Controllers/CoreController.h"


class FoodRule;

FoodSystem::FoodSystem() : BaseSystem(FOOD)
{
}


FoodSystem::~FoodSystem()
{
    satisfiedLog.Dispose();
    unsatisfiedLog.Dispose();
}

/**
 * \brief Registers a new food plot in the system
 * \param plot Plot to be registered
 */
void FoodSystem::Register(Plot* plot)
{
    (*plot).Register(new Food(plot));
    BaseSystem::Register(plot);
}

/**
 * \brief Updates food system. Tally scores for food pltos
 */
void FoodSystem::Update()
{
    for (int i = 0; i < plots.Count(); ++i)
    {
        const auto plot = plots[i];
        // Do this if you want to get the plot type (class food)
        //const auto rule = dynamic_cast<Food*> (plot->GetPlotType());
        
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
    auto log = new Log(citizen->Coords(), new FoodRule(*dynamic_cast<FoodRule*>(rule)), citizen);
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
    auto log = new Log(citizen->Coords(), new FoodRule(*dynamic_cast<FoodRule*>(rule)), citizen);
    unsatisfiedLog.InsertLast(log);
}


/**
 * \brief Resets the day (clears log & resets plots)
 */
void FoodSystem::ResetDay()
{
    for (int i = 0; i < plots.Count(); ++i)
    {
        plots[i]->GetPlotType()->Reset();
    }
    unsatisfiedLog.Dispose();
    satisfiedLog.Dispose();
}
