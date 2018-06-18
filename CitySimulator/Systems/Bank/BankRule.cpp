#include "BankRule.h"
#include "../../Controllers/CoreController.h"
#include "BankSystem.h"
#include "Bank.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"

BankRule::BankRule(Citizen& citizen) : BaseRule(citizen, BANK), saving(200.f)
{
}

BankRule::~BankRule() = default;

float BankRule::CalculateScore()
{
	if ((citizen->GetMoney() < CITIZEN_MAX_MONEY) && (saving > 100))
		return 100001;
	
    return 0;
}

/**
* \brief Attemps to find a plot that can satisfy this rule
* \return True if successfully found a plot to satisfy rule, otherwise false
*/
bool BankRule::FindPlot()
{
	auto &plots = CoreController::Instance()->GetSystemController()->GetSystem(BANK)->Plots();
	// Get a list of plots that fulfill out requirements ( distance < max distance)
	//auto coords = citizen->Coords();

	Plot* chosen = nullptr;
	auto coords = this->citizen->Coords();
	for (auto && plot : plots)
	{
		//this is a citizen pointer pointing to the citizen 
		if (chosen == nullptr)
			chosen = plot;
		else {
			const auto distance = plot->Coords().Distance(coords);
			if (distance < chosen->Coords().Distance(coords)) {
				chosen = plot;
			}
		}
	}

	// If such a list doesn't exist. This rule returns failed result false
	if (chosen == nullptr)
	{
		return false;
	}
	//CITIZEN must setActiveRule of some rule ex: bankRule
	citizen->SetActiveRule(this);
	//citizen must setActiveRule of a plot as a target;
	citizen->SetTarget(chosen);

	return true;
}

void BankRule::EnterPlot(Plot* plot)
{
	const auto bank = dynamic_cast<Bank*>(plot->GetPlotType());
	citizen->Wait(1.f);
	bank->Enter();
}

/**
* \brief Citizen withdraws money on leaving
* \param plot Plot thats is being left.
*/
void BankRule::LeavePlot(Plot* plot)
{
	const auto bank = dynamic_cast<Bank*>(plot->GetPlotType());
    
	const int moneyToWithdraw = Clamp<int>(CITIZEN_MAX_MONEY - this->citizen->GetMoney(), 0, int(saving));        
	if (moneyToWithdraw >= bank->transactionCost)
		citizen->IncreaseMoney(moneyToWithdraw - bank->transactionCost);
}

/**
* \brief Update events of food rule. Decreases citizen's hunger
*/
void BankRule::Update()
{
	//this->hungerLevel -= CoreController::Instance()->GetDeltaTime() * 30;
	//Bank Rules need not update anything;
}

/**
* \brief Returns bool to tell if citizen is satisfied with it's food requirements
* \return True if hunger level is over 20
*/
bool BankRule::IsSatisfied()
{
	//need to adjust this rate
	return saving > 10000;
}

void BankRule::saveMoney(float moneyInflow)
{
}
