#include "WorkSystem.h"
#include "Work.h"
#include "WorkRule.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"
using helper::Time;


/**
 * \brief 
 */
WorkSystem::WorkSystem(): BaseSystem(WORK)
{
	toggleable = true;
	WorkRule::timeToWork = Time(8, 0);
	WorkRule::breakTime = Time(12, 0);
	WorkRule::endBreakTime = Time(13, 0);
	WorkRule::timeOffWork = Time(17, 0);
	highLevel = false;	
}


/**
 * \brief 
 */
WorkSystem::~WorkSystem() = default;


/**
* \brief Registers a new work plot in the system
* \param plot Plot to be registered
*/
int WorkSystem::Register(Plot* plot)
{
	plot->Register(new Work(plot));
	BaseSystem::Register(plot);
    return Cost();
}

/**
* \brief Updates work system. Tally scores for work plots
*/
void WorkSystem::Update()
{
}


float WorkSystem::GetSatisfaction() const
{
	int totalEmployee = 0;
	int totalLateEmployee = 0;
	int total = 0;
	float totalWorkingTime = 0.f;
	for (auto&& plot : plots)
	{
		const auto work = dynamic_cast<Work*>(plot->GetPlotType());
		totalEmployee += work->todayEmployee;
		totalLateEmployee += work->todayLateEmployee;
		total += work->employees.Count();
		totalWorkingTime += work->todayWorkingTime;
	}

	float satisfaction = totalWorkingTime / (total * 4 * 2);

	/*
	float satisfaction = float(totalEmployee - totalLateEmployee) / (total * 2);
	cout << totalEmployee << ", " << totalLateEmployee << ", " << total * 2 << std::endl;
	*/

	satisfaction = Clamp(satisfaction, 0.f, 1.f);
	return satisfaction;
}

/**
* \brief Resets the day (clears log & resets plots)
*/
void WorkSystem::EndDay()
{
	for (auto && plot : plots)
	{
		plot->GetPlotType()->EndDay();
	}
}

void WorkSystem::Toggle()
{
	highLevel = !highLevel;
}

int WorkSystem::Cost() const
{
    if (highLevel)
    {
        return cost[1];
    }
    return cost[0];
}

std::string WorkSystem::ContentString()
{
	std::stringstream ss;

	int total = 0;
	int totalEmployee = 0;
	int totalLateEmployee = 0;
	for (auto&& plot : plots)
	{
		const auto work = dynamic_cast<Work*>(plot->GetPlotType());
		total += work->employees.Count();
		totalEmployee += work->todayEmployee;
		totalLateEmployee += work->todayLateEmployee;
	}
	if(totalLateEmployee == 0 && totalEmployee == total * 2)
    {
        ss << "Everyone was on time" << std::endl << "to work" << std::endl;
    }
	else
	{
        ss << "Total employees: " << total << std::endl;
		if (totalLateEmployee != 0)
        {
            ss << "Late:            " << totalLateEmployee / 2 << std::endl;
        }
		if (totalEmployee != total * 2)
        {
            ss << "Missing:         " << total - totalEmployee / 2 << std::endl;
        }
	}
    
	if (highLevel)
	{
		ss  << std::endl << "Building:" << std::endl << "Advanced Work: $" << Cost() << std::endl << "Only for citizen with" 
	       << std::endl << "high education level" << std::endl << std::endl;
	}
	else
	{
		ss  << std::endl << "Building:" << std::endl << "General Work:  $" << Cost() << std::endl << "Every citizen can enter" 
	    << std::endl << std::endl << std::endl;
	}

	return ss.str();
}
