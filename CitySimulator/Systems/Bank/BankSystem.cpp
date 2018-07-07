#include "BankSystem.h"
#include "Bank.h"
#include "BankRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"

class BankRule;

BankSystem::BankSystem() : BaseSystem(BANK)
{
}

BankSystem::~BankSystem() = default;

/**
* \brief Registers a new food plot in the system
* \param plot Plot to be registered
*/
int BankSystem::Register(Plot* plot)
{
	(*plot).Register(new Bank(plot));
	BaseSystem::Register(plot);
    return 0;
}

/**
* \brief Updates food system. Tally scores for food pltos
*/
void BankSystem::Update()
{
	for (auto && plot : plots)
	{
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
void BankSystem::LogSatisfied(Citizen* citizen, BaseRule* rule)
{
	// Dynamic cast rule to create a snapshot copy 
	const auto log = new Log(citizen->Coords(), new BankRule(*dynamic_cast<BankRule*>(rule)), citizen);
	satisfiedLog.InsertLast(log);
}


/**
* \brief Logs a citizen being unsatisified with a food
* \param citizen Citzen being logged
* \param rule Rule being logged
*/
void BankSystem::LogUnsatisfied(Citizen* citizen, BaseRule* rule)
{
	// Dynamic cast rule to create a snapshot copy 
	const auto log = new Log(citizen->Coords(), new BankRule(*dynamic_cast<BankRule*>(rule)), citizen);
	unsatisfiedLog.InsertLast(log);
}


/**
* \brief Resets the day (clears log & resets plots)
*/
void BankSystem::EndDay()
{
	for (auto && plot : plots)
	{
		plot->GetPlotType()->EndDay();
	}
	unsatisfiedLog.Dispose();
	satisfiedLog.Dispose();
}

void BankSystem::NewDay()
{
	for (auto plot : plots)
	{
		plot->GetPlotType()->NewDay();
	}
}
std::string BankSystem::ContentString()
{
	std::stringstream ss;
	ss << "People can only carry" << std::endl;
	ss <<"$1000. To consume, they" << std::endl;
	ss << "they must withdraw"<<std::endl << "deposits from banks" << std::endl << "banks."<<std::endl;
	ss << "12345678911234567891123456789";
	return ss.str();

}
