#include "HomeRule.h"
#include "Home.h"
#include "../Base/BaseSystem.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SystemController.h"
#include <iostream>

HomeRule::HomeRule(Citizen& citizen) : BaseRule(citizen, HOME), myHome(nullptr), atHomeFlag(false)
{
    //this is the time when people start to go home
    //TODO: goHomeTime is now a static member, which is like a curfew right now. it could be private member
    //therefore each citizen can go home by unique timing
    
    wakeUpTime = helper::Time(6);
    goHomeTime = helper::Time(21);
    
    const auto father = citizen.GetFamilyMember(FATHER);
    // TODO : seems weird
    if (father != nullptr)
    {
        const auto fatherHome = dynamic_cast<HomeRule*>(father->FindRule(HOME));
        if (Pathable(fatherHome->myHome->GetPlot()->Coords(), citizen.Coords()))
        {
            myHome = fatherHome->myHome;
            myHome->Register(this->citizen);
        }
        else
        {
            myHome = nullptr;
        }
    }
    else
    {
        DecideHome();
    }
    // TODO : They won't be home on the first day before then
    homelessLevel = 0;
    sleepingHour = 0;
}

HomeRule::~HomeRule()
{
    Unregister();
}

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
    auto & plots = CoreController::GetSystemController()->GetSystem(HOME)->Plots();
    Plot* chosen = nullptr;
    int shortestDis = INT_MAX;

    // TODO : picking a close home doesn't make as much sense? What about picking a home with the least amount of people
    for (auto&& plot : plots)
    {
        auto coord = plot->Coords();
        // Skip home if not pathable
        if (!Pathable(citizen->Coords(), coord)) continue;
        const auto home = dynamic_cast<Home*>(plot->GetPlotType());
        auto livable = true;
        if (citizen->Age() >= WORKING_AGE)
        {
            livable = !home->Full();
        }
        
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
 
    auto home = dynamic_cast<Home*>(chosen->GetPlotType());
    home->Register(citizen);
    myHome = home;
    return true;
}

bool HomeRule::FindPlot()
{
    if (myHome == nullptr)
    {
        return false;
    }

    citizen->SetActiveRule(this);
    citizen->SetTarget(myHome->GetPlot());
    return true;
}

void HomeRule::EnterPlot(Plot* plot)
{
    if (myHome == nullptr) return;
    atHomeFlag = true;
    atHomeTime = CoreController::Instance()->GetTime();
    if (atHomeTime.Hour <= wakeUpTime.Hour)
    {
        sleepingHour = float(wakeUpTime.Hour - atHomeTime.Hour) + float(RandomInt(-30, 30)) / 60.f;
    }
    else if (atHomeTime.Hour > goHomeTime.Hour)
    {
        sleepingHour = float(24 - goHomeTime.Hour + wakeUpTime.Hour - 1) + float(RandomInt(-30, 30)) / 60.f;
    }
    else
    {
        sleepingHour = 1.f;
    }
    
    citizen->Wait(sleepingHour);
}

/**
* \brief Fills up the citizen's hunger on leaving
* \param plot Plot thats is being left. Redudant. Only for interface requirements
*/
void HomeRule::LeavePlot(Plot* plot)
{
    atHomeFlag = false;
    homelessLevel = 0;
}

/**
* \brief Update events of home rule. Citizen would started to go home after 9:00
	and the desire of going home would reach it's peak at 10:00
*/
void HomeRule::Update()
{
    const auto time = CoreController::Instance()->GetTime();
	if (!AtHome() && (time.Hour == (goHomeTime.Hour - 1)))
	{
		homelessLevel = 2;
	}
    if (!AtHome() && time> goHomeTime)
    {
        const int deltaTime = time - goHomeTime;
		if (deltaTime <= 60)
		{
			homelessLevel = std::pow(2, deltaTime / 2);
		}
		else
			homelessLevel = INT_MAX;
    }
}

void HomeRule::EndDay()
{
    
}

void HomeRule::NewDay()
{
    if (!HasHome() && citizen->Age() >= WORKING_AGE)
    {
        DecideHome();
    }
}

void HomeRule::Unregister()
{
    if (myHome != nullptr)
    {
        myHome->Unregister(citizen);
        myHome = nullptr;
    }
}

float HomeRule::GetSleepTime() const
{
    return HasHome() ? sleepingHour : 0.f;
}
