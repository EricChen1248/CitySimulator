#include "HospitalRule.h"
#include "../../Controllers/CoreController.h"
#include "HospitalSystem.h"
#include "Hospital.h"
#include "../Food/FoodRule.h"
#include "../../Helpers/HelperFunctions.h"

HospitalRule::HospitalRule(Citizen& citizen): BaseRule(citizen, HOSPITAL), assignedHospital(nullptr)
{
}

HospitalRule::~HospitalRule() = default;

float HospitalRule::CalculateScore()
{
    // TODO: the biggest 
    if(enter) 
        return 50000;  
     
    return 0;
}

/**
 * \brief Attemps to find a plot that can satisfy this rule
 * \return True if successfully found a plot to satisfy rule, otherwise false
 */
bool HospitalRule::FindPlot()
{
	if (assignedHospital == nullptr)
		return false;

	citizen->SetActiveRule(this);
	citizen->SetTarget(assignedHospital);
	return true;
}

void HospitalRule::EnterPlot(Plot* plot)
{
    // TODO: Implement properly
    return;
    const auto food = dynamic_cast<Hospital*>(plot->GetPlotType());
    citizen->Wait(1.f);
    //citizen->IncreaseMoney(-food->cost);
    food->Enter();
}

/**
 * \brief Fills up the citizen's hunger on leaving
 * \param plot Plot thats is being left. Redudant. Only for interface requirements
 */
void HospitalRule::LeavePlot(Plot* plot)
{
}

/**
 * \brief Update events of food rule. Decreases citizen's hunger
 */
void HospitalRule::Update()
{
}

/**
 * \brief Returns bool to tell if citizen is satisfied with it's food requirements
 * \return True if hunger level is over 20
 */
bool HospitalRule::IsSatisfied()
{
    return true;
}

void HospitalRule::Register()
{


	auto &plots = CoreController::GetSystemController()->GetSystem(WORK)->Plots();
	// Get a list of plots that fulfill out requirements ( distance < max distance
	List<Plot*> choices;
	for (auto && plot : plots)
	{
		auto coords = citizen->Coords();
		if (!Pathable(coords, plot->Coords())) continue;
		const auto distance = plot->Coords().Distance(coords);
		if (distance < maxDistance)
		{
			auto p = plot;
			choices.InsertLast(p);
		}
	}

	// If such a list doesn't exist. This rule returns failed result false
	// TODO: �[�j�j���d��I
	if (choices.Count() == 0)
	{
		return;
	}

	const auto chosen = choices[RandomInt(0, choices.Count())];

	this->assignedHospital = chosen; // and then constant
	citizen->SetActiveRule(this);
	citizen->SetTarget(chosen);

	// To Get FoodRule
	FoodRule* foodRule = dynamic_cast<FoodRule*>(citizen->FindRule(FOOD));
	foodRule->FillHunger(); // set hungerLevel to MAX

}