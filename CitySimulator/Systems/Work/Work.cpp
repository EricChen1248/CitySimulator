#include "Work.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"


Work::Work(Plot *plot) : Base(plot, WORK)
{
	salary = CoreController::RandomInt(50, 100);
	production = salary * 2;
	earnings = 0;
	color = WORK_COLOR;
}


/**
* \brief Reset's Work Plot (earnings to 0)
*/
void Work::Reset()
{
	earnings = 0;
}

/**
* \brief New entry ( +earnings )
*/
void Work::Enter()
{
	earnings += (production - salary);
}
