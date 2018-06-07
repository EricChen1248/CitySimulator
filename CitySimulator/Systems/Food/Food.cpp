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
 * \brief Reset's Food Plot (score to 0)
 */
void Food::Reset()
{
    score = -50;
}


/**
 * \brief New entry ( +score )
 */
void Food::Enter()
{
    score += cost;
}
