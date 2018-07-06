#include "WorkRule.h"
#include "Work.h"
#include "../Bank/BankRule.h"
#include "../Base/BaseSystem.h"
#include "../School/SchoolRule.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/CoreController.h"

using helper::Time;

Time WorkRule::timeToWork;
Time WorkRule::breakTime;
Time WorkRule::endBreakTime;
Time WorkRule::timeOffWork;



/**
 * \brief 
 * \param citizen 
 */
WorkRule::WorkRule(Citizen& citizen) : BaseRule(citizen, WORK), assignedCompany(nullptr), salary(0.), baseSalary(0.), workingTime(0), earlyToWork(0)
{
}

WorkRule::~WorkRule() = default;


/**
 * \brief 
 * \return 
 */
float WorkRule::CalculateScore()
{
	if (assignedCompany != nullptr)
	{
		const Time currentTime = CoreController::Instance()->GetTime();

		// morning to work
		if((timeToWork - currentTime) < (earlyToWork + 30) && currentTime < breakTime)
		{
			// start to have score 30 min before time that  
			return 5000000 - Clamp(timeToWork - currentTime - earlyToWork, 0) * 100000;
		}
		
		// break time (want to back company)
		if (currentTime > breakTime && timeOffWork < currentTime)
		{
			return 5000000 + Clamp(currentTime - breakTime, 0) * 100000;
		}

	}
    return 0; // not have work
}

/**
* if 
* \return True if successfully found a plot to satisfy rule, otherwise false
*/
bool WorkRule::FindPlot()
{
	if (assignedCompany == nullptr)
		return false;

	citizen->SetActiveRule(this);
	citizen->SetTarget(assignedCompany);
	return true;
}

/**
 * \brief 
 * \param plot 
 */
void WorkRule::EnterPlot(Plot* plot)
{
	const auto work = dynamic_cast<Work*>(plot->GetPlotType());
    if (work == nullptr) return;
    
	const Time currentTime = CoreController::Instance()->GetTime();
	if (currentTime < breakTime)
	{
		workingTime = static_cast<float>(breakTime - currentTime) / 60;
		earlyToWork += (240 - (breakTime - currentTime));
	}
	else
		workingTime = static_cast<float>(timeOffWork - currentTime) / 60;

	float tempWorkingTime = workingTime; // satisfaction increases due to early arrival

	if (workingTime > 4)
		workingTime = 4;

	// Off Work on time
	// Adjust randomly(+-10min) to avoid rush
	citizen->Wait(workingTime + float(RandomInt(-10, 10)) / 60); 
    
	const int workingExp = citizen->Age() - 18; // Salary increases due to experience
	work->Enter(tempWorkingTime, (salary + workingExp * 0.3f) * workingTime / 4);
}

/**
* \Give citizen his/her pay for 4 hour
*/
void WorkRule::LeavePlot(Plot* plot)
{
	BankRule* bankRule = dynamic_cast<BankRule*>(citizen->FindRule(BANK));

    const int workingExp = citizen->Age() - 18; // Salary increases due to experience
	bankRule->SaveMoney((salary + workingExp * 0.3f) * workingTime / 4);

	const Time currentTime = CoreController::Instance()->GetTime();
	if (endBreakTime > currentTime) // morning session
		citizen->ForceRule(FOOD, 0.5);
}

/**
* \Do nothing
*/
void WorkRule::Update()
{
	// Do Nothing
}

/**
* \brief Returns bool to tell if citizen is satisfied with it's food requirements
* \return True if hunger level is over 20
*/
bool WorkRule::IsSatisfied()
{
	// TODO:If the person is late to work, he/she is unsatisfied;
	return true;
}

void WorkRule::NewDay()
{

	if (citizen->Age() >= 18 && citizen->Age() < 45)
	{
		if(assignedCompany == nullptr )
			Register();
		else if(earlyToWork > 60) // TODO : 60?
		{
			Plot* oldPlot = assignedCompany;
			Register();

			if (assignedCompany != oldPlot) // Check if citizen change work
			{
				const auto oldCompany = dynamic_cast<Work*>(oldPlot->GetPlotType());
				oldCompany->Resignation();
			}
		}
	}
}

/**
* \the first time a person gets his/her work
* \
*/

void WorkRule::Register()
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
	// TODO: Increase Searching area¡I
	if (choices.Count() == 0)
	{
		return;
	}

	const auto chosen = choices[RandomInt(0, choices.Count())];

	this->assignedCompany = chosen; // and then constant
	citizen->SetActiveRule(this);
	citizen->SetTarget(chosen);

	// Adjust salary due to education level
	// To Get SchoolRule
	SchoolRule* schoolRule = dynamic_cast<SchoolRule*>(citizen->FindRule(SCHOOL));

	// TODO : School Rule doesn't exist yet.
	int educationLv = schoolRule != nullptr ? schoolRule->getEdLvl() : 0;
	const auto work = dynamic_cast<Work*>(chosen->GetPlotType());
	baseSalary = work->baseSalary * RandomInt(10, 13) / 10;
	salary = baseSalary + educationLv * 0.3f; // TODO : number(education)
	work->NewEmployee();
}

void WorkRule::UnRegister()
{
	if (assignedCompany != nullptr)
	{
		// TODO : amount of people at work --
		assignedCompany = nullptr;
	}
	salary = 0;
}
