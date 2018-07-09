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
    averageWaitingTime = 0;
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
    for (auto plot : plots)
    {
        plot->GetPlotType()->NewDay();
    }
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
    averageWaitingTime = 0;
    for (auto plot : plots)
    {
        const auto bank = dynamic_cast<Bank*>(plot->GetPlotType());
        customerScore += (float(bank->CustomerCount()) / 100.f) / float(plots.Count());
        averageCustomerPerBank += float(bank->CustomerCount()) / float(plots.Count());
    }
    auto citizens = CoreController::GetSystemController()->GetCitizens();
    for (auto citizen : citizens)
    {
        const auto bankRule = dynamic_cast<BankRule*>(citizen->FindRule(BANK));
        timeScore += ((0.5f - bankRule->GetWaitingTime()) / 0.5f) / float(citizens.Count());
        averageWaitingTime += bankRule->GetWaitingTime() / float(citizens.Count());
    }
    if (customerScore <= 0.3f)
    {
        ss << "Banks aren't earning" << std::endl;
        ss << "enough money.";
    }
    if (timeScore <= 0.6f)
    {
        ss << "Build more banks" << std::endl;
        ss << "to handle everyone";
    }
    ss << std::endl;
    ss << "Average Customer:" << int(averageCustomerPerBank) << std::endl;
    ss << "Average waiting time:" << std::endl << std::fixed << std::setprecision(2) << averageWaitingTime << std::endl;
    return ss.str();
}

float BankSystem::GetSatisfaction() const
{
    float score = 0.f;
    for (auto plot : plots)
    {
        const auto bank = dynamic_cast<Bank*>(plot->GetPlotType());
        score += (float(bank->CustomerCount()) / 100.f) / float(plots.Count());
    }
    
    score = Clamp(score, score, 0.5f);
    
    auto citizens = CoreController::GetSystemController()->GetCitizens();
    for (auto citizen : citizens)
    {
        const auto bankRule = dynamic_cast<BankRule*>(citizen->FindRule(BANK));
        score += (0.5f - bankRule->GetWaitingTime()) / 0.5f / float(citizens.Count() * 2);
    }
    return Clamp(score, 0.f, 1.f);
}
