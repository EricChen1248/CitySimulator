#include "SchoolRule.h"
#include "SchoolSystem.h"
#include "School.h"
#include "../Food/FoodRule.hpp" 
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Logger.h"

using helper::Time;

Time SchoolRule::schoolStartTime;
Time SchoolRule::schoolEndTime;

SchoolRule::SchoolRule(Citizen& citizen): BaseRule(citizen, SCHOOL), educationLevel(0)
{
	earlyToSchool = 0;
}

SchoolRule::~SchoolRule()
{
    UnRegister();
};

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
		return 2000000.f - Clamp(schoolStartTime - currentTime - earlyToSchool - 30, 0) * 100000.f;
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
* \brief Calculates student learning time and education level. Also feeds them lunch
* \param plot
*/
void SchoolRule::EnterPlot(Plot* plot)
{
	const auto school = dynamic_cast<School*>(plot->GetPlotType());
	school->Enter();
    const auto time = CoreController::Instance()->GetTime();
    const auto learnTime = float(schoolEndTime - time) / 60;
    educationLevel += assignedSchool->isPremium ? 18 * learnTime : 12 * learnTime;

	FoodRule* foodRule = dynamic_cast<FoodRule*>(citizen->FindRule(FOOD));
	const auto hunger = Clamp(foodRule->Hunger() + 40, 0.f, 100.f);
	foodRule->FillHunger(hunger);
    citizen->Wait(learnTime);
}

/**
 * \brief Interface requirement
 * \param plot Plot thats is being left. Redudant. Only for interface requirements
 */
void SchoolRule::LeavePlot(Plot* plot)
{
    
}

void SchoolRule::NewDay()
{
	if (citizen->Age() > 18) return;
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
		UnRegister();
	    break;
	case 18:
	    Logger::Log("Education Level:" + std::to_string(educationLevel));
	    UnRegister();
	    return;
	default: break;
	}

	if (assignedSchool != nullptr) return;
	auto & plots = CoreController::GetSystemController()->GetSystem(SCHOOL)->Plots();
	// Get a list of plots
    
	List<School*> choices;
	for (auto && plot : plots)
	{
	    const auto coords = citizen->Coords();
		if (!Pathable(coords, plot->Coords())) continue;
	    const auto school = dynamic_cast<School*>(plot->GetPlotType());
	    if (school->IsFull()) continue; 
		choices.InsertLast(school);
	}

	// If such a list doesn't exist. This rule returns failed result false
	if (choices.Count() == 0) return;

	const auto chosen = choices[RandomInt(0, choices.Count())];

	assignedSchool = chosen; 
    assignedSchool->NewStudent(citizen);
}

void SchoolRule::UnRegister()
{
	if (assignedSchool != nullptr)
	{
	    assignedSchool->Graduation(citizen);
		assignedSchool = nullptr;
	}
}