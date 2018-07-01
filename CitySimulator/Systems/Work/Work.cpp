#include "Work.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Government.h"


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
void Work::Enter(const float productDelta)
{
	//score += static_cast<int>(productDelta);
	Government::AddTax(productDelta * 0.1f);
}
