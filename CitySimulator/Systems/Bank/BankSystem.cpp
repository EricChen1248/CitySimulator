#include "BankSystem.h"
#include "Bank.h"
#include "BankRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include <iomanip>
class BankRule;

BankSystem::BankSystem() : BaseSystem(BANK)
{
	this->averageCustomerPerBank = 0;
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
	waitTimeList.Clear();
}
void BankSystem::NewClientWait(const float& time)
{
	waitTimeList.InsertLast(time);
}
std::string BankSystem::ContentString()
{
	std::stringstream ss;
	//ss << "People can withdraw" << std::endl;
	//ss <<"they deposit from" << std::endl;
	//ss << "banks" << std::endl;
	//ss << "They are unsatisfied if" << std::endl;
	//ss << "1.They wait too long"<<std::endl;
	//ss << "2.Each banks isn't" << std::endl;
	//ss << "  earning enough.";
	float timeScore = 0.f;
	float customerScore = 0.f;
	averageCustomerPerBank = 0;
	float averageWaitingTime = 0;
	for (auto plot : plots)
	{
		auto bank = dynamic_cast<Bank*> (plot->GetPlotType());
		customerScore += (float(bank->GetCustomer()) / 100.f) / float(plots.Count());
		averageCustomerPerBank += float(bank->GetCustomer()) / float(plots.Count());
	}

	for (auto score : waitTimeList)
	{
		timeScore += ((0.5f - score) / 0.5f) / float(waitTimeList.Count());
		averageWaitingTime += score / float(waitTimeList.Count());
	}
	if ((customerScore <= 0.3f))
	{
		ss << "Banks aren't earning" << std::endl;
		ss << "enough money.";
	}
	if ((timeScore <= 0.6f))
	{
		ss << "Build more banks" << std::endl;
		ss << "to handle everyone";
	}
	ss << std::endl;
	ss << "Average Customer:" << int (averageCustomerPerBank) << std::endl;
	ss << "Average waiting hour:" << std::endl <<  std::fixed << std::setprecision(2) << (averageWaitingTime) << std::endl;
	return ss.str();

}

float BankSystem::GetSatisfaction() const
{
	float score = 0.f;
	for (auto plot : plots)
	{
		auto bank = dynamic_cast<Bank*> (plot->GetPlotType());
		score += (float(bank->GetCustomer()) / 100.f) / float(plots.Count());
	}
	score = score >= 0.5f ? 0.5f : score;
	for (auto score : waitTimeList)
	{
		score += ((0.5f - score)/0.5f)/float(waitTimeList.Count()*2);
	}
	if (score >= 1)
		return 1.f;
	else if (score <= 0)
		return 0.f;
	else
		return score;
}
