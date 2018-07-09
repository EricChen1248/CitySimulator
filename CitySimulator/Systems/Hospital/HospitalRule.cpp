#include "Hospital.h"
#include "HospitalRule.h"
#include "HospitalSystem.h"
#include "../Bank/BankRule.h"
#include "../Base/BaseSystem.h"
#include "../Food/FoodRule.hpp"
#include "../../Collections/List.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"

HospitalRule::HospitalRule(Citizen& citizen): BaseRule(citizen, HOSPITAL), assignedHospital(nullptr)
{
}

HospitalRule::~HospitalRule() = default;

float HospitalRule::CalculateScore()
{
    if(enter) 
        return INFINITY;  
     
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
	const auto hospital = dynamic_cast<Hospital*>(plot->GetPlotType());
    if (hospital == nullptr) return;
	int cost = hospital->cost;

	BankRule* bankRule = dynamic_cast<BankRule*>(citizen->FindRule(BANK));
	if (citizen->Money() + bankRule->GetSavings() < cost)
	{
		citizen->Die();
		return;
	}

	// Today's fee
	if (citizen->Money() == 0)
		bankRule->SaveMoney(static_cast<float>(-cost));
	else if(citizen->Money() >= cost)
		citizen->IncreaseMoney(-cost);
	else
	{	
		cost -= citizen->Money();
		citizen->IncreaseMoney(-citizen->Money());
		bankRule->SaveMoney(static_cast<float>(-cost));
	}
		
	citizen->Wait(24.f);
	hospital->Enter();
}

/**
 * \brief Fills up the citizen's hunger on leaving
 * \param plot Plot thats is being left. Redudant. Only for interface requirements
 */
void HospitalRule::LeavePlot(Plot* plot)
{
	// Die randomly
	// TODO : this set is random or not ??????
    const int die = RandomInt(50, 100);
	if (die < citizen->Age())
	{
		citizen->Die();
		return;
	}

	citizen->ForceRule(HOSPITAL, 24.f);
}

void HospitalRule::EndDay()
{
	// Die accidentally
	// TODO : probability & Get Real Satisfaction
    const float satisfaction =  dynamic_cast<HospitalSystem*>(CoreController::GetSystemController()->GetSystem(HOSPITAL))->satisfactionToday;
	if (satisfaction < 0.85 && RandomInt(0, 85) >= satisfaction * 100)
    {
	    // TODO : hospital death is disabled
        //citizen->Die();
    }
}

void HospitalRule::Register()
{
	auto &plots = CoreController::GetSystemController()->GetSystem(HOSPITAL)->Plots();
	// Get a list of plots that fulfill out requirements ( distance < max distance
	List<Plot*> choices;
	auto coords = citizen->Coords();

	int count = 0;
	// If such a list doesn't exist. This rule returns failed result false
	// TODO: ¥[¤j·j¯Á½d³ò¡I

	while (choices.Count() == 0)
	{
		count++;
		if (RIGHT - LEFT < count * deltaIncrease)
        {
            break;
        }

		for (auto && plot : plots)
		{
			if (!Pathable(coords, plot->Coords())) continue;
			const auto distance = plot->Coords().Distance(coords);
			const auto hospital = dynamic_cast<Hospital*>(plot->GetPlotType());
			if (distance < count * deltaIncrease && !hospital->IsFull())
			{
				choices.InsertLast(plot);
			}
		}
	}

	if (choices.Count() == 0)
	{
		citizen->Die(); // If a person can't find hospital, he/she will die soon
		return;
	}

	const auto chosen = choices[RandomInt(0, choices.Count())];

	this->assignedHospital = chosen; // and then constant
	enter = true;

	const auto hospital = dynamic_cast<Hospital*>(chosen->GetPlotType());
	hospital->NewMember(citizen);

	// To Get FoodRule
	FoodRule* foodRule = dynamic_cast<FoodRule*>(citizen->FindRule(FOOD));
	foodRule->FillHunger(); // set hungerLevel to MAX
}



