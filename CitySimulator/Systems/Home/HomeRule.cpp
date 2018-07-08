#include "HomeRule.h"
#include "Home.h"
#include "../Base/BaseSystem.h"
#include "../../Controllers/SystemController.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
#include <iostream>
HomeRule::HomeRule(Citizen& citizen) : BaseRule(citizen, HOME),myHome(nullptr),atHomeFlag(false)
{
	//this is the time when people start to go home
	//TODO: goHomeTime is now a static member, which is like a curvew right now. it could be private member
	//therefore each citizen can go home by unique timing
	goHomeTime.IncreaseTime(20);
	wakeUpTime.IncreaseTime(6);
	if (citizen.GetFamilyMember(FATHER) != nullptr)
	{
		if (Pathable(dynamic_cast<HomeRule*>(citizen.GetFamilyMember(FATHER)->FindRule(HOME))->myHome->GetPlot()->Coords(), citizen.Coords()))
			myHome = dynamic_cast<HomeRule*>(citizen.GetFamilyMember(FATHER)->FindRule(HOME))->myHome;
		else
			myHome = nullptr;
	}
	else
	{
		DecideHome();
	}
	homelessLevel = 0;
	sleepingHour = 0;
}

HomeRule::~HomeRule() = default;

float HomeRule::CalculateScore()
{
	return static_cast<float>(homelessLevel);
}

/**
* \brief: attempt to find a home for the citizen.
* \Detail Algorithm: if citizen is under age 20, they can live under over-occupied house
* \Detail Algorithm: citizen above age 20, has to find a house where it's not over-occupied.
* \return True if successfully found a plot to satisfy rule, otherwise false
*/
bool HomeRule::DecideHome()
{
	auto &plots = CoreController::GetSystemController()->GetSystem(HOME)->Plots();
	Plot* chosen = nullptr;
	int shortestDis = 1000;
    
	for (auto && plot : plots) 
	{
		auto coord = plot->Coords();
	    // Skip home if not pathable
	    if (!Pathable(citizen->Coords(), coord)) continue;
		const auto home = dynamic_cast<Home*>(plot->GetPlotType());
		auto livable = true;
		if (citizen->Age() >= 20)
			 livable = (!home->Full());
		if (livable && citizen->Coords().Distance(coord) <= shortestDis)
		{
			chosen = plot;
			shortestDis = citizen->Coords().Distance(coord);
		}
	}
    
	if (chosen == nullptr)
	{
		return false;
	}
	else
	{
		auto home = dynamic_cast<Home*>(chosen->GetPlotType());
		home->Register(citizen);
		myHome = home;
		return true;
	}
}

bool HomeRule::FindPlot()
{
	if (myHome == nullptr)
	{
		return false;
	}
	else
	{
		citizen->SetActiveRule(this);
		citizen->SetTarget(myHome->GetPlot());
		return true;
	}
}
void HomeRule::EnterPlot(Plot* plot)
{
	if (myHome == nullptr) return;
	atHomeFlag = true;
	homelessLevel = 0;
	atHomeTime = CoreController::Instance()->GetTime();
	if (atHomeTime.Hour <= wakeUpTime.Hour)
	{
		sleepingHour = float(wakeUpTime.Hour - atHomeTime.Hour) + float(RandomInt(-30,30)/60.f);
	}
	else if (atHomeTime.Hour > goHomeTime.Hour)
	{
		sleepingHour = float(24-goHomeTime.Hour) + float(wakeUpTime.Hour-1) + float(RandomInt(-30, 30) / 60.f);
	}
	else
	{
		sleepingHour = 1.f;
	}
	citizen->Wait(sleepingHour);
	myHome -> Enter();
}

/**
* \brief Fills up the citizen's hunger on leaving
* \param plot Plot thats is being left. Redudant. Only for interface requirements
*/
void HomeRule::LeavePlot(Plot* plot)
{
	std::string leaveTime = CoreController::Instance()->GetTime().ToString();
	//std::cout << "citizen wakes up at " << leaveTime << std::endl;
	atHomeFlag = false;
	/*Nothing happend need to discuss */
}

/**
* \brief Update events of food rule. Decreases citizen's hunger
*/
void HomeRule::Update()
{
	
	// TODO : if homeless hour exceed certain critirea , this citizen sholud
    const auto time = CoreController::Instance()->GetTime();
	if ((time.Hour >= goHomeTime.Hour)&&(!AtHome()))
	{
		homelessLevel = 2000000000;
	}
	if((time.Hour < wakeUpTime.Hour)&&(!AtHome()))
	{
		homelessLevel = 2000000000;
	}
}

void HomeRule::NewDay()
{
	if (myHome == nullptr && citizen->Age() > WORKING_AGE)
	{
		DecideHome();
		return;
	}
}

void HomeRule::EndDay() 
{
	return;
}

float HomeRule::GetSleepTime() const
{
	if (HasHome())
		return sleepingHour;
	else
		return 0.f;
}
