#include "Food.hpp"
#include "FoodRule.hpp"
#include "FoodSystem.hpp"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"

const int Food::MEAL_COST[3] {80,120,180};

Food::Food(Plot* plot) : Base(plot, FOOD), earnedMoney(0), overloadedTally(0)
{
    cost = 1000;
    mealDeltaCost = RandomInt(-5, 5);
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
        ss << "There were too many " << std::endl << "customers to handle!" << std::endl << std::endl;
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

int Food::FoodCost(const helper::Time& time) const
{
    
    if (time < FoodRule::breakfastTime)
    {
        return MEAL_COST[0] + mealDeltaCost;
    }
    
    if(time < FoodRule::lunchTime)
    {
        return MEAL_COST[1] + mealDeltaCost;
    }
    
    return MEAL_COST[2] + mealDeltaCost;
    
}
/**
 * \brief New entry ( +score )
 */
void Food::Enter()
{
    const auto& time = CoreController::Instance()->GetTime();
    const auto cost = FoodCost(time);
    earnedMoney += cost;
    
    if (plot->GetOccupantCount() > maxCustomer)
    {
        overloadedTally++;
    }
    Government::AddTax(cost * 0.15f);
}
