#include "HomeSystem.h"
#include "Home.h"
#include "HomeRule.h"
#include "../Work/WorkRule.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/CoreController.h"

HomeSystem::HomeSystem():BaseSystem(HOME)
{
}
int HomeSystem::Register(Plot* plot) 
{
	//plot need to register a base first;
	//base(home) will assign a ramdom capacity 
	plot->Register(new Home(plot));
	//Because BaseSystem is not a virtual function, and we didn't and have to overload FUNCTION REGISTER
	BaseSystem::Register(plot);
    return 0;
}

HomeSystem::~HomeSystem() = default;
void HomeSystem::Update() 
{
	//I believe home need not need to updata on a daily bases
	score = 0;
}

/*
brief:
TODO:Adding more grading system
should be adjusted to whether they have convinent live,
how long does it take them to work : friend Workrule;
>> how far is their job from their work, and how many building are arround.
*/
float HomeSystem::GetSatisfaction() const
{
	auto citizenList = CoreController::GetSystemController()->GetCitizens();
	float count = 0.f;
	float avgSleepHour = 0.f;
	//how many people have house;
	for (auto citizen : citizenList)
	{
		//count how many people have house
		dynamic_cast<HomeRule*>(citizen->FindRule(HOME))->HasHome() == true ? count += (1.f/float(citizenList.Count())): count += 0;
		avgSleepHour += (dynamic_cast<HomeRule*>(citizen->FindRule(HOME))->GetSleepTime()/8.f)/float(citizenList.Count());
	}
	count = (0.5f * count) + (0.5f * avgSleepHour);
	if (count >= 1.f)
		return 1;
	else
		return count;
}
void HomeSystem::EndDay()
{
	for (auto && plot : plots)
	{
		plot->GetPlotType()->EndDay();
	}
	unsatisfiedLog.Dispose();
	satisfiedLog.Dispose();
}

int HomeSystem::GetTotalFamily() const
{
	int count = 0;
	auto citizenList = CoreController::GetSystemController()->GetCitizens();
	for (auto citizen : citizenList)
	{
		if (citizen->Age() >= WORKING_AGE)
		{
			if (citizen->GetGender() == MALE)
			{
				count++;
			}
			else
			{
				if (!citizen->IsMarried())
					count++;
			}
		}
	}
	return count;
}

std::string HomeSystem::ContentString()
{
	std::stringstream ss;
	//ss << "Provide your citizen" << std::endl;
	//ss << "a warm house. People" << std::endl;
	//ss << "get unsatisfied if" << std::endl;
	//ss << "1.don't have home." << std::endl;
	//ss << "2.Home is too far, thus" << std::endl;
	//ss << "  don't sleep much.";
	auto citizenList = CoreController::GetSystemController()->GetCitizens();
	float count = 0.f;
	float avgSleepHour = 0.f;
	//how many people have house;
	for (auto citizen : citizenList)
	{
		//count how many people have house
		dynamic_cast<HomeRule*>(citizen->FindRule(HOME))->HasHome() == true ? count += (1.f / float(citizenList.Count())) : count += 0;
		avgSleepHour += (dynamic_cast<HomeRule*>(citizen->FindRule(HOME))->GetSleepTime()) / float(citizenList.Count());
	}
	if (count < 0.8f)
	{
		ss << "Build more home to" << std::endl << "handle homeless people." << std::endl;
	}
	if (avgSleepHour < 6.f)
	{
		ss << "People go home late," << std::endl << "perhaps relocate some" << std::endl << "home?"<<std::endl;
	}
	if ((count > 0.8f) && (avgSleepHour > 6.f))
	{
		ss << "Citizen are very" << std::endl << "satisfied." << std::endl;
	}
	ss << std::endl;
	ss << "Homeless people: " << int ((1.f-count)*float(citizenList.Count())) << std::endl;
	ss << "Avg Sleeping hour: " << std::fixed << std::setprecision(2) << avgSleepHour;
	return ss.str();
}
