#include "WorkSystem.h"
#include "Work.h"
#include "WorkRule.h"
#include "../../Helpers/Time.h"
#include "../../Helpers/HelperFunctions.h"



class WorkRule;

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
	(*plot).Register(new Work(plot));
	BaseSystem::Register(plot);
    return 0;
}

/**
* \brief Updates work system. Tally scores for work plots
*/
void WorkSystem::Update()
{
	/*
	for (auto && plot : plots)
	{
		// Do this if you want to get the plot type (class work)
		//const auto rule = dynamic_cast<Work*> (plot->GetPlotType());

		// Tallying and adding score for occupant count. Positive for within limit people, negative for over
		const auto count = plot->GetOccupantCount();
		score += (std::min(count, maxOccupantCount) * scorePerOccupant - std::max(count - maxOccupantCount, 0) * overPenalty) * CoreController::Instance()->GetDeltaTime();
	}
	*/
}


float WorkSystem::GetSatisfaction() const
{
	int employeeCount = 0;
	float todayWorkTIme = 0.f;
	for (auto&& plot : plots)
	{
		const auto work = dynamic_cast<Work*>(plot->GetPlotType());
		employeeCount += work->employees.Count();
		todayWorkTIme += work->todayWorkTime;
	}

	float satisfaction = todayWorkTIme / (employeeCount * 4 * 2);

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

int WorkSystem::Cost()
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
    ss << "Everyone was on time" << std::endl << "to work" << std::endl;
    
	if (highLevel)
	{
		ss << std::endl << "Building:" << std::endl << "Advanced Work $" << Cost() << std::endl << "Only for citizen with" 
	       << std::endl << "high education level" << std::endl << std::endl;
	}
	else
	{
		ss <<  std::endl << "Building:" << std::endl << "General Work $" << Cost() << std::endl << "Every citizen can enter" 
	    << std::endl << std::endl << std::endl;
	}

	return ss.str();
}
