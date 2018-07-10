#include "SchoolRule.h"
#include "SchoolSystem.h"
#include "School.h"
#include "../Food/FoodRule.hpp" 
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/CoreController.h"

using helper::Time;

Time SchoolRule::schoolStartTime;
Time SchoolRule::schoolEndTime;

SchoolRule::SchoolRule(Citizen& citizen): BaseRule(citizen, SCHOOL), educationLevel(0)
{
	earlyToSchool = 0;
}

SchoolRule::~SchoolRule() = default;

float SchoolRule::CalculateScore()
{
    if (citizen->Age() >= 18) return 0;
	if (assignedSchool == nullptr) return 0;
	
	const Time currentTime = CoreController::Instance()->GetTime();

    if (schoolEndTime < currentTime) return 0;
    
	// morning to school
	if (schoolStartTime - currentTime < earlyToSchool + 60)
	{
		// start to have score 30 min before time that  
		return 5000000 - Clamp(schoolStartTime - currentTime - earlyToSchool - 60, 0) * 100000;
	}

	return 0; // not have school
}

/**
 * \brief Attemps to find a plot that can satisfy this rule
 * \return True if successfully found a plot to satisfy rule, otherwise false
 */
bool SchoolRule::FindPlot()
{
	if (assignedSchool == nullptr)
	{
		return false;
	}
	
	citizen->SetActiveRule(this);
	citizen->SetTarget(assignedSchool->plot);
	return true;
}

/**
* \brief 
* \param plot
*/
void SchoolRule::EnterPlot(Plot* plot)
{
	const auto school = dynamic_cast<School*>(plot->GetPlotType());
	school->Enter();
    const auto time = CoreController::Instance()->GetTime();
    citizen->Wait(float(schoolEndTime - time) / 60);
}

/**
 * \brief Fills up the students's hunger on leaving. Accumulate education level.
 * \param plot Plot thats is being left. Redudant. Only for interface requirements
 */
void SchoolRule::LeavePlot(Plot* plot)
{
	if (assignedSchool->isPremium)
	{
		educationLevel += 90;
	}
	else
	{
		educationLevel += 60;
	}

	//Fills up the students's hunger needs

	FoodRule* foodRule = dynamic_cast<FoodRule*>(citizen->FindRule(FOOD));
	const int hunger = Clamp(foodRule->Hunger() + 40, 0.f, 100.f);
	foodRule->FillHunger(hunger);
}

void SchoolRule::NewDay()
{
	if (citizen->Age() >= 18) return;
	Register();
}

/**
 * \brief 
 */
void SchoolRule::Update()
{
	//do nothing
}

void SchoolRule::Register()
{
	switch (citizen->Age())
	{
	case 0:
	case 6:
	case 12:
	case 18:
		UnRegister();
		break;
	}

	if (assignedSchool != nullptr)
	{
		return;
	}
	auto &plots = CoreController::GetSystemController()->GetSystem(SCHOOL)->Plots();
	// Get a list of plots
	List<Plot*> choices;
	for (auto && plot : plots)
	{
		auto coords = citizen->Coords();
		if (!Pathable(coords, plot->Coords())) continue;
		const auto distance = plot->Coords().Distance(coords);
		auto p = plot;
		choices.InsertLast(p);
	}

	// If such a list doesn't exist. This rule returns failed result false
	if (choices.Count() == 0)
	{
		return;
	}

	const auto chosen = choices[RandomInt(0, choices.Count())];

	this->assignedSchool = dynamic_cast<School*>(chosen->GetPlotType()); 
}

void SchoolRule::UnRegister()
{
	if (assignedSchool != nullptr)
	{
		assignedSchool = nullptr;
	}
}