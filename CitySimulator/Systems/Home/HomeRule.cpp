#include "HomeRule.h"
#include "../../Controllers/CoreController.h"
#include "HomeSystem.h"
#include "Home.h"
#include "../../Helpers/Constants.h"
#include "../../Collections/List.h"
#include <math.h>

HomeRule::HomeRule(Citizen& citizen) : BaseRule(citizen),myHome(nullptr)
{
	homelessLevel = 0;
	homelessHour = 0;
}

HomeRule::~HomeRule() = default;

float HomeRule::CalculateScore()
{
	return homelessLevel;
}

/**
* \brief Attemps to find a plot that can satisfy this rule
* \return True if successfully found a plot to satisfy rule, otherwise false
*/
bool HomeRule::FindPlot()
{
	auto &plots = CoreController::Instance()->GetSystemController()->GetSystem(HOME)->Plots();
	// Get a list of plots that fulfill out requirements ( distance < max distance)
	//auto coords = citizen->Coords();
	Plot* chosen = nullptr;
	if (myHome == nullptr) 
	{
		int maxDistance = 100;
		auto coord = citizen->Coords();
		for (auto && plot : plots)
		{
			auto home = dynamic_cast<Home*>(plot->GetPlotType());
			if (!home->Full())
			{
				if (maxDistance >= plot->Coords().Distance(coord))
				{
					maxDistance = plot->Coords().Distance(coord);
					chosen = plot;
				}
			}
		}
		// If such a list doesn't exist. This rule returns failed result false
		if (chosen == nullptr)
		{
			return false;
		}
		auto home = dynamic_cast<Home*>(chosen->GetPlotType());
		home->Register(citizen);
		myHome = home;
	}

	//CITIZEN must setActiveRule of some rule ex: bankRule
	citizen->SetActiveRule(this);
	//citizen must setActiveRule of a plot as a target;
	citizen->SetTarget(myHome->GetPlot());

	return true;
}

void HomeRule::EnterPlot(Plot* plot)
{
	const auto home = dynamic_cast<Home*>(plot->GetPlotType());
	citizen->Wait(3.f);
	home -> Enter();
}

/**
* \brief Fills up the citizen's hunger on leaving
* \param plot Plot thats is being left. Redudant. Only for interface requirements
*/
void HomeRule::LeavePlot(Plot* plot)
{
	/*Nothing happend need to discuss */
}

/**
* \brief Update events of food rule. Decreases citizen's hunger
*/
void HomeRule::Update()
{
	// TODO : Tweak HomelessHour to time ratio
	if (myHome == nullptr)
	{
		//need rescaling
		homelessHour += CoreController::Instance()->GetDeltaTime();
		homelessLevel = std::exp((homelessHour-50)/100);
		if (CoreController::Instance()->GetTime().Hour == 10)
			homelessLevel = 1000000000;
	}
	else
		homelessHour = 0;
}

/**
* \brief Returns bool to tell if citizen is satisfied with it's food requirements
* \return True if hunger level is over 20
*/
bool HomeRule::IsSatisfied()
{
	//need to adjust this rate
	return homelessLevel < 50;
}
