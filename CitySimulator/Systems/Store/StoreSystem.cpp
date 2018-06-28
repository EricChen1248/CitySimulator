#include "StoreSystem.h"
#include "Store.h"
#include "StoreRule.h"
#include "../../Controllers/CoreController.h"


class StoreRule;

StoreSystem::StoreSystem() : BaseSystem(STORE)
{
}


StoreSystem::~StoreSystem() = default;

/**
* \brief Registers a new Store plot in the system
* \param plot Plot to be registered
*/
void StoreSystem::Register(Plot* plot)
{
	(*plot).Register(new Store(plot));
	BaseSystem::Register(plot);
}

/**
* \brief Updates Store system. Tally scores for Store pltos
*/
void StoreSystem::Update()
{
	for (auto && plot : plots)
	{
		// Do this if you want to get the plot type (class Store)
		//const auto rule = dynamic_cast<Store*> (plot->GetPlotType());

		// Tallying and adding score for occupant count. Positive for within limit people, negative for over
		const auto count = plot->GetOccupantCount();
		score += (std::min(count, maxOccupantCount) * scorePerOccupant - std::max(count - maxOccupantCount, 0) * overPenalty) * CoreController::Instance()->GetDeltaTime();
	}
}

/**
* \brief Logs a citizen being satisified with a Store
* \param citizen Citzen being logged
* \param rule Rule being logged
*/
void StoreSystem::LogSatisfied(Citizen* citizen, BaseRule* rule)
{
	// Dynamic cast rule to create a snapshot copy 
	auto log = new Log(citizen->Coords(), new StoreRule(*dynamic_cast<StoreRule*>(rule)), citizen);
	satisfiedLog.InsertLast(log);
}


/**
* \brief Logs a citizen being unsatisified with a Store
* \param citizen Citzen being logged
* \param rule Rule being logged
*/
void StoreSystem::LogUnsatisfied(Citizen* citizen, BaseRule* rule)
{
	// Dynamic cast rule to create a snapshot copy 
	auto log = new Log(citizen->Coords(), new StoreRule(*dynamic_cast<StoreRule*>(rule)), citizen);
	unsatisfiedLog.InsertLast(log);
}


/**
* \brief Resets the day (clears log & resets plots)
*/
void StoreSystem::EndDay()
{
	for (auto && plot : plots)
	{
		plot->GetPlotType()->EndDay();
	}
	unsatisfiedLog.Dispose();
	satisfiedLog.Dispose();
}
