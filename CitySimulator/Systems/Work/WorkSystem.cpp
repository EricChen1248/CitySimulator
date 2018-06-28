#include "WorkSystem.h"
#include "Work.h"
#include "WorkRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Time.h"

class WorkRule;

using helper::Time;
/**
 * \brief 
 */
WorkSystem::WorkSystem(): BaseSystem(WORK)
{
	WorkRule::timeToWork = Time(8, 0);
	WorkRule::breakTime = Time(12, 0);
	WorkRule::endBreakTime = Time(13, 0);
	WorkRule::timeOffWork = Time(17, 0);
}


/**
 * \brief 
 */
WorkSystem::~WorkSystem() = default;


/**
* \brief Registers a new work plot in the system
* \param plot Plot to be registered
*/
void WorkSystem::Register(Plot* plot)
{
	(*plot).Register(new Work(plot));
	BaseSystem::Register(plot);
}

/**
* \brief Updates work system. Tally scores for work plots
*/
void WorkSystem::Update()
{
	/*
	for (auto && plot : plots)
	{
		// Do this if you want to get the plot type (class work)
		//const auto rule = dynamic_cast<Work*> (plot->GetPlotType());

		// Tallying and adding score for occupant count. Positive for within limit people, negative for over
		const auto count = plot->GetOccupantCount();
		score += (std::min(count, maxOccupantCount) * scorePerOccupant - std::max(count - maxOccupantCount, 0) * overPenalty) * CoreController::Instance()->GetDeltaTime();
	}
	*/
}

/**
* \brief Logs a citizen being satisified with a work
* \param citizen Citzen being logged
* \param rule Rule being logged
*/
void WorkSystem::LogSatisfied(Citizen* citizen, BaseRule* rule)
{
	// Dynamic cast rule to create a snapshot copy 
	auto log = new Log(citizen->Coords(), new WorkRule(*dynamic_cast<WorkRule*>(rule)), citizen);
	satisfiedLog.InsertLast(log);
}


/**
* \brief Logs a citizen being unsatisified with a Work
* \param citizen Citzen being logged
* \param rule Rule being logged
*/
void WorkSystem::LogUnsatisfied(Citizen* citizen, BaseRule* rule)
{
	// Dynamic cast rule to create a snapshot copy 
	auto log = new Log(citizen->Coords(), new WorkRule(*dynamic_cast<WorkRule*>(rule)), citizen);
	unsatisfiedLog.InsertLast(log);
}


/**
* \brief Resets the day (clears log & resets plots)
*/
void WorkSystem::EndDay()
{
	for (auto && plot : plots)
	{
		plot->GetPlotType()->EndDay();
	}
	unsatisfiedLog.Dispose();
	satisfiedLog.Dispose();
}

