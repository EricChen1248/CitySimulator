#include "Food.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/Government.h"

Food::Food(Plot* plot) : Base(plot, FOOD), customerCountTally(0), overloadedTally(0)
{
    cost = RandomInt(50, 100);
    score = 0;
    color = FOOD_COLOR;
}

/**
 * \brief EndDay's Food Plot (score to 0)
 */
void Food::EndDay()
{
    score = -50;
    customerCountTally = 0;
    overloadedTally = 0;
}


/**
 * \brief New entry ( +score )
 */
void Food::Enter()
{
    ++customerCountTally;
    if (plot->GetOccupantCount() > maxCustomer)
    {
        overloadedTally++;
    }
    Government::AddTax(cost * 0.1f);
}
