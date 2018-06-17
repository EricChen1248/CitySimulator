#include "Work.h"
#include "WorkRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"


/**
 * \brief 
 * \param plot 
 */
Work::Work(Plot *plot) : Base(plot, WORK)
{

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
void Work::Enter(int productDelta)
{
	score += productDelta;
}
