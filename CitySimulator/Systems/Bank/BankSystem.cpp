#include "BankSystem.h"
#include "Bank.h"
#include "BankRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include <iomanip>
class BankRule;

BankSystem::BankSystem() : BaseSystem(BANK)
{
    averageCustomerPerBank = 0;
}

BankSystem::~BankSystem() = default;

/**
* \brief Registers a new food plot in the system
* \param plot Plot to be registered
*/
int BankSystem::Register(Plot* plot)
{
    plot->Register(new Bank(plot));
    BaseSystem::Register(plot);
    return Cost();
}

/**
* \brief Updates food system. Tally scores for food pltos
*/
void BankSystem::Update()
{
}

void BankSystem::NewDay()
{
	for (auto&& plot : plots)
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
	for (auto && plot : plots)
	{
		auto&& bank = dynamic_cast<Bank*> (plot->GetPlotType());
		customerScore += (float(bank->CustomerCount()) / 100.f) / float(plots.Count());
		averageCustomerPerBank += float(bank->CustomerCount()) / float(plots.Count());
	}

	for (auto&&score : waitTimeList)
	{
		timeScore += ((0.5f - score) / 0.5f) / float(waitTimeList.Count());
		averageWaitingTime += score / float(waitTimeList.Count());
	}
	if ((customerScore <= 0.3f))
	{
		ss << "Banks aren't earning" << std::endl;
		ss << "enough money."<<std::endl;
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
	for (auto&& plot : plots)
	{
		auto&& bank = dynamic_cast<Bank*> (plot->GetPlotType());
		score += (float(bank->CustomerCount()) / 100.f) / float(plots.Count());
	}
	score = score >= 0.5f ? 0.5f : score;
	for (auto&& waitscore : waitTimeList)
	{
		score += ((0.5f - waitscore)/0.5f)/float(waitTimeList.Count()*2);
	}
	if (waitTimeList.Count() == 0)
		score += 0.5f;
	if (score >= 1)
		return 1.f;
	else if (score <= 0)
		return 0.f;
	else
		return score;
}
