#include "Work.h"
#include "WorkRule.h"
#include "WorkSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Government.h"
#include "../../Helpers/HelperFunctions.h"
#include "../Base/BaseSystem.h"
#include <iostream>

using namespace std;


/**
 * \brief 
 * \param plot 
 */
Work::Work(Plot *plot) : Base(plot, WORK), todayWorkTime(0.f), todayEmployee(0), todayEarlyEmployee(0), todayLateEmployee(0), production(0) // TODO : cost;
{

	highLevel = dynamic_cast<WorkSystem*>(CoreController::GetSystemController()->GetSystem(WORK))->highLevel;
	color = WORK_COLOR; // TODO : different color for different level
	if (highLevel)
	{
		baseSalary = float(RandomInt(80, 120)); // TODO : salary
		cost = RandomInt(80, MAX_WORK_COST);
	}
	else
	{
		baseSalary = float(RandomInt(50, 100)); // TODO : salary
		cost = RandomInt(50, 80);
	}
}

/**
* \brief EndDay's Work Plot (score to 0)
*/
void Work::EndDay()
{
	score = 0;
}

/**
* \brief NewDay's Work Plot (todayWorkTime to 0)
*/
void Work::NewDay()
{
	todayEmployee = 0;
	todayEarlyEmployee = 0;
	todayLateEmployee = 0;
	todayWorkTime = 0.f;
	production = 0;
}

/**
* \brief New entry ( +score )
*/
void Work::Enter(const float workingTime, const float production)
{
	//score += static_cast<int>(productDelta);
	this->production += production;
	Government::AddTax(production * 0.1f);
	todayWorkTime += workingTime;

	if (workingTime == 4)
	{
		todayEmployee += 1;
	}
	else if (workingTime < 4)
	{
		todayLateEmployee += 1;
	}
	else
	{
		todayEarlyEmployee += 1;
	}

}


int Work::Destroy()
{
	for (auto && employee : employees)
	{
		WorkRule* workRule = dynamic_cast<WorkRule*>(employee->FindRule(WORK));
		workRule->assignedCompany = nullptr;
	}
	return cost;
}

std::string Work::ContentString()
{
	std::stringstream ss;
	if (highLevel)
		ss << "High-Level Company" << std::endl;
	else
		ss << "General Company" << std::endl;

	if (float(todayLateEmployee / 2) / employees.Count() >= 0.1)
	{
		ss << "Too many people" << std::endl << "were late." << std::endl << std::endl;
	}
	else if (float(todayLateEmployee / 2) / employees.Count() > 0)
	{
		ss << "Still some people" << std::endl << "were late." << std::endl << std::endl;
	}
	else
	{
		ss << "Today was an" << std::endl << "excellent day." << std::endl << std::endl;
	}

	ss << "Employees: " << employees.Count() << " people"
		<< std::endl << "Late: " << todayLateEmployee / 2 << " people"
		<< std::endl << "On time: " << employees.Count() - todayLateEmployee / 2 << " people";
	return ss.str();
}

void Work::NewEmployee(Citizen* citizen)
{
	employees.InsertLast(citizen);
}

void Work::Resignation(Citizen* citizen)
{
	employees.Remove(citizen);
}