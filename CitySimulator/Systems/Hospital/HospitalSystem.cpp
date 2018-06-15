#include "HospitalSystem.h"
#include "Hospital.h"
#include "HospitalRule.h"
#include "../../Controllers/CoreController.h"


class HospitalRule;

HospitalSystem::HospitalSystem() : BaseSystem(FOOD)
{
}


HospitalSystem::~HospitalSystem() = default;

/**
 * \brief Registers a new food plot in the system
 * \param plot Plot to be registered
 */
void HospitalSystem::Register(Plot* plot)
{
    (*plot).Register(new Hospital(plot));
    BaseSystem::Register(plot);
}

/**
 * \brief Updates food system. Tally scores for food pltos
 */
void HospitalSystem::Update()
{
    for (auto && plot : plots)
    {
        // Do this if you want to get the plot type (class food)
        //const auto rule = dynamic_cast<Hospital*> (plot->GetPlotType());
        
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
void HospitalSystem::LogSatisfied(Citizen* citizen, BaseRule* rule)
{
    // Dynamic cast rule to create a snapshot copy 
    auto log = new Log(citizen->Coords(), new HospitalRule(*dynamic_cast<HospitalRule*>(rule)), citizen);
    satisfiedLog.InsertLast(log);
}


/**
 * \brief Logs a citizen being unsatisified with a food
 * \param citizen Citzen being logged
 * \param rule Rule being logged
 */
void HospitalSystem::LogUnsatisfied(Citizen* citizen, BaseRule* rule)
{
    // Dynamic cast rule to create a snapshot copy 
    auto log = new Log(citizen->Coords(), new HospitalRule(*dynamic_cast<HospitalRule*>(rule)), citizen);
    unsatisfiedLog.InsertLast(log);
}


/**
 * \brief Resets the day (clears log & resets plots)
 */
void HospitalSystem::ResetDay()
{
    for (auto && plot : plots)
    {
        plot->GetPlotType()->EndDay();
    }
    unsatisfiedLog.Dispose();
    satisfiedLog.Dispose();
}
