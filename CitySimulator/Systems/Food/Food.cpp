#include "Food.hpp"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"
#include "FoodSystem.hpp"

const int Food::MAX_FOOD_COST;

Food::Food(Plot* plot) : Base(plot, FOOD), earnedMoney(0), overloadedTally(0)
{
    cost = 1000;
    mealCost = RandomInt(50, MAX_FOOD_COST);
    color = FOOD_COLOR;
}

Food::~Food()
= default;

std::string Food::ContentString()
{
    std::stringstream ss;
    if (earnedMoney < FoodSystem::OPERATING_COST)
    {
        ss << "We did not earn" << std::endl << "enough money today" << std::endl << std::endl;
    }
    else if (overloadedTally > 20)
    {
        ss << "There were too many " << std::endl << "customers to handle!" << std::endl;
    }
    else
    {
        ss << "Today was an" << std::endl << "excellent day." << std::endl << std::endl;
    }
    ss << "Today's earnings: " << earnedMoney << std::endl << "Overloaded count: " << overloadedTally;
    return ss.str();
}

void Food::NewDay()
{
    earnedMoney = 0;
    overloadedTally = 0;
}

/**
 * \brief New entry ( +score )
 */
void Food::Enter()
{
    earnedMoney += mealCost * 0.5f;
    if (plot->GetOccupantCount() > maxCustomer)
    {
        overloadedTally++;
    }
    Government::AddTax(mealCost * 0.1f);
}
