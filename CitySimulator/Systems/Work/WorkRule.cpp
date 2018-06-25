#include "WorkRule.h"
#include "Work.h"
#include "../School/SchoolRule.h"
#include "../Bank/BankRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"

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
	// To Get BankRule
	SchoolRule* schoolRule = dynamic_cast<SchoolRule*>(citizen.FindRule(SCHOOL));
    const int educationLv = schoolRule->getEdLvl();
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
    const Time currentTime = CoreController::Instance()->GetTime();


	// Now is not work time
	if (timeToWork > currentTime || currentTime > timeOffWork)
	{
		return 0;
	}

	// break time
	if (endBreakTime > currentTime || currentTime > breakTime)
	{
		citizen->ForceRule(FOOD, 1.f);
	}

	return 500000;
}

/**
* if 
* \return True if successfully found a plot to satisfy rule, otherwise false
*/
bool WorkRule::FindPlot()
{
	auto &plots = CoreController::Instance()->GetSystemController()->GetSystem(WORK)->Plots();
	if (assignedCompany == nullptr)
	{
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
		// TODO: 加大搜索範圍！
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
	citizen->Wait(4.f); // 4 hour (waited to adjust)
	work->Enter(static_cast<int>(production - salary));
}

/**
* \Give citizen his/her pay for 4 hour
*/
void WorkRule::LeavePlot(Plot* plot)
{
	BankRule* bankRule = dynamic_cast<BankRule*>(citizen->FindRule(BANK));
	bankRule->saveMoney(this->salary);
}

/**
* \Do nothing
*/
void WorkRule::Update()
{

}

/**
* \brief Returns bool to tell if citizen is satisfied with it's food requirements
* \return True if hunger level is over 20
*/
bool WorkRule::IsSatisfied()
{
	return true;
}

// TODO: 工作滿意度?