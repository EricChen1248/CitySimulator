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
void HomeSystem::LogSatisfied(Citizen* citizen, BaseRule* rule)
{
	// Dynamic cast rule to create a snapshot copy 
	const auto log = new Log(citizen->Coords(), new HomeRule(*dynamic_cast<HomeRule*>(rule)), citizen);
	satisfiedLog.InsertLast(log);
}


/**
* \brief Logs a citizen being unsatisified with a food
* \param citizen Citzen being logged
* \param rule Rule being logged
*/
void HomeSystem::LogUnsatisfied(Citizen* citizen, BaseRule* rule)
{
	// Dynamic cast rule to create a snapshot copy 
	const auto log = new Log(citizen->Coords(), new HomeRule(*dynamic_cast<HomeRule*>(rule)), citizen);
	unsatisfiedLog.InsertLast(log);
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
		dynamic_cast<HomeRule*>(citizen->FindRule(HOME))->IsSatisfied() == true ? count += (1.f/float(citizenList.Count())): count += 0;
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
