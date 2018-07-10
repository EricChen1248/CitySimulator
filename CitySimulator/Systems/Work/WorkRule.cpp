#include "WorkRule.h"
#include "Work.h"
#include "WorkSystem.h"
#include "../Bank/BankRule.h"
#include "../Base/BaseSystem.h"
#include "../School/SchoolRule.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Logger.h"


using helper::Time;
Time WorkRule::timeToWork;
Time WorkRule::breakTime;
Time WorkRule::endBreakTime;
Time WorkRule::timeOffWork;

/**
 * \brief 
 * \param citizen 
 */
WorkRule::WorkRule(Citizen& citizen) : BaseRule(citizen, WORK), shiftCount(0), assignedCompany(nullptr),
                                       salary(0.), baseSalary(0.), workingTime(0), earlyToWork(0) {}

WorkRule::~WorkRule()
{
    UnRegister();
};


/**
 * \brief 
 * \return 
 */
float WorkRule::CalculateScore()
{
    if (assignedCompany == nullptr) return 0;
    
	const Time currentTime = CoreController::Instance()->GetTime();

	// morning to work
	if(shiftCount < 1 && timeToWork - currentTime < earlyToWork + 60 && currentTime < breakTime )
	{
		// start to have score 30 min before time that  
		return 5000000 - Clamp(timeToWork - currentTime - earlyToWork - 60, 0) * 100000;
	}
		
	// break time (want to back company)
	if (shiftCount < 2 && breakTime < currentTime && currentTime < timeOffWork)
	{
		return 5000000 + Clamp(currentTime - breakTime, 0) * 100000;
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
 
    ++shiftCount;
	const Time currentTime = CoreController::Instance()->GetTime();
	if (currentTime < breakTime)
	{
		workingTime = static_cast<float>(breakTime - currentTime) / 60;
		earlyToWork += 240 - (breakTime - currentTime);
	}
	else
    {
        workingTime = static_cast<float>(timeOffWork - currentTime) / 60;
    }
    
    workingTime = Clamp(workingTime, 0.f, 4.f);

	// Off Work on time
	// Adjust randomly(+-10min) to avoid rush
	citizen->Wait(workingTime + float(RandomInt(-10, 10)) / 60); 
	const int workingExp = citizen->Age() - 18; // Salary increases due to experience
	work->Enter(workingTime, (salary + workingExp * 0.3f) * workingTime / 4);
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
		citizen->ForceRule(FOOD);
}

/**
* \Do nothing
*/
void WorkRule::Update()
{
	// Do Nothing
}

void WorkRule::EndDay()
{
    
}

void WorkRule::NewDay()
{
    shiftCount = 0;

	if (citizen->Age() >= 18 && citizen->Age() < 45)
	{
		if(assignedCompany == nullptr )
			Register();
		else if(earlyToWork > 60) // TODO : 60?
		{
			Plot* oldPlot = assignedCompany;

			if (Register()) // Check if citizen change work
			{
				const auto oldCompany = dynamic_cast<Work*>(oldPlot->GetPlotType());
				oldCompany->Resignation(citizen);
			}
		}
	}
}

/**
* \the first time a person gets his/her work
* \
*/

bool WorkRule::Register()
{
    List<Plot*> choices;
	auto &highplots = dynamic_cast<WorkSystem*>(CoreController::GetSystemController()->GetSystem(WORK))->highWork;
	auto &lowplots = dynamic_cast<WorkSystem*>(CoreController::GetSystemController()->GetSystem(WORK))->lowWork;

	auto coords = citizen->Coords();

	// To Get SchoolRule
	SchoolRule* schoolRule = dynamic_cast<SchoolRule*>(citizen->FindRule(SCHOOL));
	const int educationLv = schoolRule->EducationLevel();
	bool isHighEducation = educationLv > 50; // TODO : 50

	// Get a list of plots that fulfill out requirements ( distance < max distance )
	if (isHighEducation)
	{
		for (auto && plot : highplots)
		{
			if (!Pathable(coords, plot->Coords())) continue;
			const auto distance = plot->Coords().Distance(coords);
			if (distance < maxDistance)
			{
				auto p = plot;
				choices.InsertLast(p);
			}
		}

	}

	if (choices.Count() == 0)
	{
		for (auto && plot : lowplots)
		{
			if (!Pathable(coords, plot->Coords())) continue;
			const auto distance = plot->Coords().Distance(coords);
			if (distance < maxDistance)
			{
				auto p = plot;
				choices.InsertLast(p);
			}
		}
	}
    
	if (choices.Count() == 0)
	{
		return false;
	}

	const auto chosen = choices[RandomInt(0, choices.Count())];

	this->assignedCompany = chosen; // and then constant

	// Adjust salary due to education level
    const auto work = dynamic_cast<Work*>(chosen->GetPlotType());
	baseSalary = work->baseSalary * RandomInt(10, 13) / 10;
	
    salary = baseSalary + educationLv * 0.3f; // TODO : number(education)
	work->NewEmployee(citizen);
    return true;
}

void WorkRule::UnRegister()
{
	if (assignedCompany != nullptr)
	{
		auto work = dynamic_cast<Work*>(assignedCompany->GetPlotType());
		work->Resignation(citizen);
		assignedCompany = nullptr;
	}
	salary = 0;
}
