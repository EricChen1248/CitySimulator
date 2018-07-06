#include "Work.h"
#include "WorkRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Government.h"
#include "../../Helpers/HelperFunctions.h"


/**
 * \brief 
 * \param plot 
 */
Work::Work(Plot *plot) : Base(plot, WORK), todayWorkTime(0.f), cost(RandomInt(50, MAX_WORK_COST)), todayEmployee(0), todayEarlyEmployee(0), todayLateEmployee(0), production(0) // TODO : cost;
{
	score = 0;
	color = WORK_COLOR;
	baseSalary = float(RandomInt(50, 100)); // TODO : salary
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
		todayEmployee += 1;
	else if (workingTime < 4)
		todayLateEmployee += 1;
	else 
		todayEarlyEmployee += 1;

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

	ss << "Today's earnings: " << production << std::endl << "Employees: " << employees.Count() << " people"
		<< std::endl << "Late to work: " << todayLateEmployee / 2 << " people"
		<< std::endl << "Early to work: " << todayEarlyEmployee / 2 << " people"
		<< std::endl << "Not go to work: " << (employees.Count() - todayEarlyEmployee - todayEmployee - todayLateEmployee) / 2 << " people";
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