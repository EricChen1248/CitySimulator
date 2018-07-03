#include "SchoolSystem.h"
#include "School.h"
#include "SchoolRule.h"
#include "../../Controllers/CoreController.h"


class SchoolRule;

SchoolSystem::SchoolSystem() : BaseSystem(SCHOOL)
{
}


SchoolSystem::~SchoolSystem() = default;

/**
 * \brief Registers a new food plot in the system
 * \param plot Plot to be registered
 */
int SchoolSystem::Register(Plot* plot)
{
    (*plot).Register(new School(plot));
    BaseSystem::Register(plot);
    return 0;
}

/**
 * \brief Updates food system. Tally scores for food plots
 */
void SchoolSystem::Update()
{
    for (auto && plot : plots)
    {
        // Do this if you want to get the plot type (class food)
        //const auto rule = dynamic_cast<School*> (plot->GetPlotType());
        
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
void SchoolSystem::LogSatisfied(Citizen* citizen, BaseRule* rule)
{
    // Dynamic cast rule to create a snapshot copy 
    auto log = new Log(citizen->Coords(), new SchoolRule(*dynamic_cast<SchoolRule*>(rule)), citizen);
    satisfiedLog.InsertLast(log);
}


/**
 * \brief Logs a citizen being unsatisified with a food
 * \param citizen Citzen being logged
 * \param rule Rule being logged
 */
void SchoolSystem::LogUnsatisfied(Citizen* citizen, BaseRule* rule)
{
    // Dynamic cast rule to create a snapshot copy 
    auto log = new Log(citizen->Coords(), new SchoolRule(*dynamic_cast<SchoolRule*>(rule)), citizen);
    unsatisfiedLog.InsertLast(log);
}


/**
 * \brief Resets the day (clears log & resets plots)
 */
void SchoolSystem::EndDay()
{
    for (auto && plot : plots)
    {
        plot->GetPlotType()->EndDay();
    }
    unsatisfiedLog.Dispose();
    satisfiedLog.Dispose();
}
