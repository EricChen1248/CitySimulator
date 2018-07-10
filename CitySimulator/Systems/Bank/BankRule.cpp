#include "BankRule.h"
#include "BankSystem.h"
#include "Bank.h"
#include "../Citizen/CitizenEnum.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
#include "../Citizen/CitizenEnum.h"
#include <iostream>
#include "../../Controllers/CoreController.h"
BankRule::BankRule(Citizen& citizen) : BaseRule(citizen, BANK), saving(100000.f)
{
    moneyDownLimit = 800;
}

BankRule::~BankRule() 
= default;

float BankRule::CalculateScore()
{
    if (citizen->Money() < moneyDownLimit && saving > moneyDownLimit - citizen->Money())
    {
        return 10000;
    }
    return 0;
}

/**
* \brief Attemps to find a plot that can satisfy this rule
* \return True if successfully found a plot to satisfy rule, otherwise false
*/
bool BankRule::FindPlot()
{
    auto& plots = CoreController::GetSystemController()->GetSystem(BANK)->Plots();
    // Get a list of plots that fulfill out requirements ( distance < max distance)
    // auto coords = citizen->Coords();

    Plot* chosen = nullptr;
    auto coords = this->citizen->Coords();
    for (auto&& plot : plots)
    {
        if (!Pathable(coords, plot->Coords())) continue;
        if (chosen == nullptr)
        {
            chosen = plot;
        }
        else
        {
            const auto distance = plot->Coords().Distance(coords);
            if (distance < chosen->Coords().Distance(coords))
            {
                chosen = plot;
                break;
            }
        }
    }

    // If such a list doesn't exist. This rule returns failed result false
    if (chosen == nullptr)
    {
        return false;
    }
    citizen->SetActiveRule(this);
    citizen->SetTarget(chosen);
    return true;
}

void BankRule::EnterPlot(Plot* plot)
{
    const auto& bank = dynamic_cast<Bank*>(plot->GetPlotType());
    if (bank == nullptr) return;
	const int peopleNow = plot->GetOccupantCount();
	float waitingTime = 0.05f*float(peopleNow);
	auto bankSys = dynamic_cast<BankSystem*>(CoreController::Instance()->GetSystemController()->GetSystem(BANK));
	bankSys->NewClientWait(waitingTime*60.f);
    citizen->Wait(waitingTime);
    bank->Enter();
}

/**
* \brief Citizen withdraws money on leaving
* \param plot Plot thats is being left.
*/
void BankRule::LeavePlot(Plot* plot)
{
    const auto bank = dynamic_cast<Bank*>(plot->GetPlotType());
    int moneyToWithdraw;
    if (citizen->Age() >= WORKING_AGE)
    {
        moneyToWithdraw = Clamp(CITIZEN_MAX_MONEY - this->citizen->Money(), 0, int(saving));

        if (moneyToWithdraw >= bank->transactionCost)
        {
            citizen->IncreaseMoney(moneyToWithdraw - bank->transactionCost);
            saving -= moneyToWithdraw;
        }
    }
    else
    {
        if (citizen->GetFamilyMember(FATHER) != nullptr)
        {
            auto fatherBankRule = dynamic_cast<BankRule*>(citizen->GetFamilyMember(FATHER)->FindRule(BANK));
            auto motherBankRule = dynamic_cast<BankRule*>(citizen->GetFamilyMember(MOTHER)->FindRule(BANK));

            moneyToWithdraw = Clamp(CITIZEN_MAX_MONEY - this->citizen->Money(), 0,
                                    int(fatherBankRule->saving + motherBankRule->saving));
            if (moneyToWithdraw > bank->transactionCost)
            {
                citizen->IncreaseMoney(moneyToWithdraw - bank->transactionCost);
                const float dadAfford = moneyToWithdraw * (fatherBankRule->saving / (fatherBankRule->saving +
                    motherBankRule->saving));
                const float momAfford = moneyToWithdraw - dadAfford;
                fatherBankRule->saving -= dadAfford;
                motherBankRule->saving -= momAfford;
            }
        }
        else
        {
            moneyToWithdraw = Clamp<int>(CITIZEN_MAX_MONEY - this->citizen->Money(), 0, int(saving));

            if (moneyToWithdraw >= bank->transactionCost)
            {
                citizen->IncreaseMoney(moneyToWithdraw - bank->transactionCost);
                saving -= moneyToWithdraw;
            }
        }
    }
    bank->earnedMoney += bank->transactionCost;
    return;
}

/**
* \brief Update events of food rule. Decreases citizen's hunger
*/
void BankRule::Update()
{
}

void BankRule::SaveMoney(const float moneyInflow)
{
    saving += moneyInflow;
}
