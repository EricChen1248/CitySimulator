#include "Food.hpp"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"
#include "FoodSystem.hpp"

const int Food::MAX_FOOD_COST;

Food::Food(Plot* plot) : Base(plot, FOOD), customerCountTally(0), overloadedTally(0)
{
    cost = RandomInt(50, MAX_FOOD_COST);
    score = 0;
    color = FOOD_COLOR;
}

Food::~Food()
= default;
std::string Food::ContentString()
{
    std::stringstream ss;
    if (customerCountTally < FoodSystem::DAILY_CUSTOMER)
    {
        ss << "Not enough people" << std::endl << "are coming here." << std::endl << std::endl;
    }
    else if (overloadedTally > 0)
    {
        ss << "There is too many " << std::endl << " customers to handle!" << std::endl;
    }
    else
    {
        ss << "The restuarant performed fine the past day." << std::endl << std::endl;
    }
    ss << "Today's customer: " << customerCountTally << std::endl << "Overloaded count: " << overloadedTally;
    return ss.str();
}

void Food::NewDay()
{
    customerCountTally = 0;
    overloadedTally = 0;
}

/**
 * \brief EndDay's Food Plot (score to 0)
 */
void Food::EndDay()
{
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
