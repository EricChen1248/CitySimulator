#include "BankRule.h"
#include "../../Controllers/CoreController.h"
#include "BankSystem.h"
#include "Bank.h"

BankRule::BankRule(Citizen& citizen) : BaseRule(citizen), hungerLevel(0)
{
}

BankRule::~BankRule() = default;

float BankaRule::CalculateScore()
{
	if (hungerLevel > 80)
	{
		return 0;
	}
	return (100 - hungerLevel) * 100;
}

/**
* \brief Attemps to find a plot that can satisfy this rule
* \return True if successfully found a plot to satisfy rule, otherwise false
*/
bool BankRule::FindPlot()
{
	auto &plots = CoreController::Instance()->GetSystemController()->GetSystem(BANK)->Plots();

	// Get a list of plots that fulfill out requirements ( distance < max distance
	List<Plot*> choices;
	for (auto && plot : plots)
	{
		auto coords = citizen->Coords();
		const auto distance = plot->Coords().Distance(coords);
		if (distance < maxDistance)
		{
			auto p = plot;
			choices.InsertLast(p);
		}
	}

	// If such a list doesn't exist. This rule returns failed result false
	if (choices.Count() == 0)
	{
		return false;
	}
	const auto chosen = choices[CoreController::RandomInt(0, choices.Count())];
	citizen->SetActiveRule(this);
	citizen->SetTarget(chosen);

	return true;
}

void BankRule::EnterPlot(Plot* plot)
{
	const auto bank = dynamic_cast<Bank*>(plot->GetPlotType());
	citizen->Wait(1.f);
	citizen->IncreaseMoney(-bank->cost);
	bank->Enter();
}

/**
* \brief Fills up the citizen's hunger on leaving
* \param plot Plot thats is being left. Redudant. Only for interface requirements
*/
void BankRule::LeavePlot(Plot* plot)
{
	hungerLevel = 100.f;
}

/**
* \brief Update events of food rule. Decreases citizen's hunger
*/
void BankRule::Update()
{
	// TODO : Tweak hunger to time ratio
	this->hungerLevel -= CoreController::Instance()->GetDeltaTime() * 30;
}

/**
* \brief Returns bool to tell if citizen is satisfied with it's food requirements
* \return True if hunger level is over 20
*/
bool BankRule::IsSatisfied()
{
	return hungerLevel > 20;
}
