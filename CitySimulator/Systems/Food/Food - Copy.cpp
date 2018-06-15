#include "Food.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"

Food::Food(Plot* plot) : Base(plot, FOOD)
{
    cost = CoreController::RandomInt(50, 100);
    score = 0;
    color = FOOD_COLOR;
}

/**
 * \brief EndDay's Food Plot (score to 0)
 */
void Food::EndDay()
{
    score = -50;
}


/**
 * \brief New entry ( +score )
 */
void Food::Enter()
{
    score += cost;
    Government::AddTax(cost * 0.1);
}
