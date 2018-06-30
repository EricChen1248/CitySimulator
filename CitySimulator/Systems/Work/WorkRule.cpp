#include "WorkRule.h"
#include "Work.h"
#include "../School/SchoolRule.h"
#include "../Bank/BankRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/PathFinder/PathFinder.h"

using helper::Time;

Time WorkRule::timeToWork;
Time WorkRule::breakTime;
Time WorkRule::endBreakTime;
Time WorkRule::timeOffWork;

/**
 * \brief 
 * \param citizen 
 */
WorkRule::WorkRule(Citizen& citizen) : BaseRule(citizen, WORK), assignedCompany(nullptr)
{
	// To Get SchoolRule
	SchoolRule* schoolRule = dynamic_cast<SchoolRule*>(citizen.FindRule(SCHOOL));

	// TODO : School Rule doesn't exist yet.
	int educationLv;

	if (schoolRule != nullptr)
		educationLv = schoolRule->getEdLvl();
	else
		educationLv = 0;

	production = static_cast<float>(RandomInt(50, 100));
	salary = production * 0.5f + educationLv * 0.3f;
}

WorkRule::~WorkRule() = default;


/**
 * \brief 
 * \return 
 */
float WorkRule::CalculateScore()
{
	if (citizen->Age() >= 18 && citizen->Age() < 45)
	{
		const Time currentTime = CoreController::Instance()->GetTime();
		// Now is not work time
		if (timeToWork > currentTime || currentTime > timeOffWork)
		{
			return 0;
		}

		// morning to work
		if((timeToWork - currentTime) < earlyToWork) {}

		// break time (want to back company)
		if (endBreakTime > currentTime || currentTime > breakTime)
		{
			return 50000;
		}

		return 500000;
	}
    return 0;
}

/**
* if 
* \return True if successfully found a plot to satisfy rule, otherwise false
*/
bool WorkRule::FindPlot()
{
	auto &plots = CoreController::GetSystemController()->GetSystem(WORK)->Plots();
	if (assignedCompany == nullptr)
	{
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
		// TODO: ¥[¤j·j¯Á½d³ò¡I
		if (choices.Count() == 0)
		{
			return false;
		}

		const auto chosen = choices[RandomInt(0, choices.Count())];

		this->assignedCompany = chosen; // and then constant
		citizen->SetActiveRule(this);
		citizen->SetTarget(chosen);
		return true;
	}

	citizen->SetActiveRule(this);
	citizen->SetTarget(this->assignedCompany);
	return true;
}

/**
 * \brief 
 * \param plot 
 */
void WorkRule::EnterPlot(Plot* plot)
{
	const auto work = dynamic_cast<Work*>(plot->GetPlotType());
	const Time currentTime = CoreController::Instance()->GetTime();
	if (currentTime < breakTime)
	{
		workingTime = static_cast<float>(breakTime - currentTime) / 60;
		earlyToWork += (240 - (breakTime - currentTime));
	}
	else
		workingTime = static_cast<float>(timeOffWork - currentTime) / 60;

	if (workingTime > 4)
		workingTime = 4;

	citizen->Wait(workingTime); // Off Work on time

    const int workingExp = citizen->Age() - 18; // Salary increases due to experience
	work->Enter((production - salary - workingExp * 0.3) * workingTime / 4);
}

/**
* \Give citizen his/her pay for 4 hour
*/
void WorkRule::LeavePlot(Plot* plot)
{
	BankRule* bankRule = dynamic_cast<BankRule*>(citizen->FindRule(BANK));

    const int workingExp = citizen->Age() - 18; // Salary increases due to experience
	bankRule->saveMoney((salary + workingExp * 0.3) * workingTime / 4);

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


/**
* \the first time a person gets his/her work
* \
*/

bool WorkRule::Register()
{
	return true;
}

bool WorkRule::UnRegister()
{
	return true;
}
