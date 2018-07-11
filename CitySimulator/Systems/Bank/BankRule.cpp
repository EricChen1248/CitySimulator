#include "BankRule.h"
#include "BankSystem.h"
#include "Bank.h"
#include "../Citizen/CitizenEnum.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/CoreController.h"

BankRule::BankRule(Citizen& citizen) : BaseRule(citizen, BANK), saving(0.f) {}

BankRule::~BankRule()
= default;

float BankRule::CalculateScore()
{
    if (citizen->Money() < CITIZEN_MIN_MONEY)
    {
        if (citizen->Age() >= WORKING_AGE)
        {
            return saving > CITIZEN_MIN_MONEY - citizen->Money() ? 5000.f : 0.f;
        }

        const auto father = citizen->GetFamilyMember(FATHER);
        const auto mother = citizen->GetFamilyMember(MOTHER);
        float parentSaving = 0;
        parentSaving += father == nullptr ? 0 : dynamic_cast<BankRule*>(father->FindRule(BANK))->GetSavings();
        parentSaving += mother == nullptr ? 0 : dynamic_cast<BankRule*>(mother->FindRule(BANK))->GetSavings();
        if (parentSaving >= CITIZEN_MIN_MONEY - citizen->Money())
            return 5000;

        return 0;
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
    const auto coords = this->citizen->Coords();
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
    const float waitingTime = 0.05f * float(peopleNow);
    auto bankSys = dynamic_cast<BankSystem*>(CoreController::GetSystemController()->GetSystem(BANK));
    bankSys->NewClientWait(waitingTime);
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

        citizen->IncreaseMoney(moneyToWithdraw);
        saving -= moneyToWithdraw;
    }
    else
    {
		if ((citizen->GetFamilyMember(FATHER) != nullptr) || (citizen->GetFamilyMember(MOTHER) != nullptr))
		{
			BankRule* fatherBankRule = nullptr;
			float fatherSaving = 0;
			if (citizen->GetFamilyMember(FATHER) != nullptr)
			{
				fatherBankRule = dynamic_cast<BankRule*>(citizen->GetFamilyMember(FATHER)->FindRule(BANK));
				fatherSaving = fatherBankRule->GetSavings();
			}
			BankRule* motherBankRule = nullptr;
			float motherSaving = 0;
			if (citizen->GetFamilyMember(MOTHER) != nullptr)
			{
				motherBankRule = dynamic_cast<BankRule*>(citizen->GetFamilyMember(MOTHER)->FindRule(BANK));
				motherSaving = motherBankRule->GetSavings();
			}
            moneyToWithdraw = Clamp(CITIZEN_MAX_MONEY - this->citizen->Money(), 0,
                                    int(fatherSaving + motherSaving));
            citizen->IncreaseMoney(moneyToWithdraw);
            const float dadAfford = moneyToWithdraw * (fatherSaving / (fatherSaving +
                motherSaving));
            const float momAfford = moneyToWithdraw - dadAfford;
			if(fatherBankRule != nullptr)
				fatherBankRule->saving -= dadAfford;
			if(motherBankRule != nullptr)
				motherBankRule->saving -= momAfford;
        }
        else
        {
            moneyToWithdraw = Clamp<int>(CITIZEN_MAX_MONEY - this->citizen->Money(), 0, int(saving));
            citizen->IncreaseMoney(moneyToWithdraw);
            saving -= moneyToWithdraw;
        }
    }
    bank->earnedMoney += bank->transactionCost;
}

/**
* \brief Update events of food rule. Decreases citizen's hunger
*/
void BankRule::Update() {}

void BankRule::SaveMoney(const float moneyInflow)
{
    saving += moneyInflow;
}
