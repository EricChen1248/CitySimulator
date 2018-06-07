#include "Work.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"


Work::Work(Plot *plot) : Base(plot, WORK)
{
	salary = CoreController::RandomInt(50, 100);
	production = salary * 2;
	score = 0;
	color = WORK_COLOR;
}


/**
* \brief EndDay's Work Plot (score to 0)
*/
void Work::EndDay()
{
	score = 0;
}

/**
* \brief New entry ( +score )
*/
void Work::Enter()
{
	score += (production - salary);
}
