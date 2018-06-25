#include "School.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"

School::School(Plot* plot) : Base(plot, SCHOOL)
{
    cost = RandomInt(50, 100);
    score = 0;
    color = FOOD_COLOR;
}

/**
 * \brief EndDay's School Plot (score to 0)
 */
void School::EndDay()
{
    score = -50;
}


/**
 * \brief New entry ( +score )
 */
void School::Enter()
{
    score += cost;
    Government::AddTax(cost * 0.1f);
}
