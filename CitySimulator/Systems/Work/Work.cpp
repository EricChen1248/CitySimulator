#include "Work.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Government.h"
#include "../../Helpers/HelperFunctions.h"


/**
 * \brief 
 * \param plot 
 */
Work::Work(Plot *plot) : Base(plot, WORK), todayWorkTime(0.f)
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
	todayWorkTime = 0.f;
}

/**
* \brief New entry ( +score )
*/
void Work::Enter(const float workingTime, const float production)
{
	//score += static_cast<int>(productDelta);
	Government::AddTax(production * 0.1f);
	todayWorkTime += workingTime;
}


int Work::Destroy()
{
	return 0;
}

std::string Work::ContentString()
{
	return " ";
}

void Work::NewEmployee()
{
	employeeCount += 1;
}

void Work::Resignation()
{
	employeeCount -= 1;
}