#include "WorkRule.h"
#include "WorkSystem.h"
#include "Work.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Time.h"



WorkRule::WorkRule(Citizen& citizen) : BaseRule(citizen), assignedCompany(nullptr)
{
}

WorkRule::~WorkRule() = default;


float WorkRule::CalculateScore()
{
	helper::Time currentTime = CoreController::Instance()->GetTime();
	helper::Time timeToWork(8, 0);
	helper::Time breakTime(12, 0);
	helper::Time endBreakTime(13, 0);
	helper::Time timeOffWork(17, 0);

	// Now is not work time
	if (timeToWork > currentTime || currentTime > timeOffWork)
	{
		return 0;
	}
	// break time
	if (endBreakTime > currentTime || currentTime > breakTime)
	{
		return 100; // Maybe citizen wants to stay at company;
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

		const auto chosen = choices[CoreController::RandomInt(0, choices.Count())];

		this->assignedCompany = chosen; // and then constant
		citizen->SetActiveRule(this);
		citizen->SetTarget(chosen);
		return true;
	}

	citizen->SetActiveRule(this);
	citizen->SetTarget(this->assignedCompany);
	return true;
}

void WorkRule::EnterPlot(Plot* plot)
{
	const auto work = dynamic_cast<Work*>(plot->GetPlotType());
	citizen->Wait(4.f); // 4 hour (waited to adjust)
	work->Enter();
}

/**
* \Give citizen his/her pay for 4 hour
*/
void WorkRule::LeavePlot(Plot* plot)
{
	const auto work = dynamic_cast<Work*>(plot->GetPlotType());
	citizen->IncreaseMoney(work->salary);
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