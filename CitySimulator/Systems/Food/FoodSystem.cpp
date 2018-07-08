#include "FoodSystem.hpp"
#include "FoodRule.hpp"
#include "Food.hpp"
#include "../../Helpers/HelperFunctions.h"


const int FoodSystem::OPERATING_COST;

FoodSystem::FoodSystem() : BaseSystem(FOOD)
{
    FoodRule::breakfastTime = helper::Time(10,0);
    FoodRule::lunchTime = helper::Time(14,0);
}

FoodSystem::~FoodSystem() = default;

/**
 * \brief Registers a new food plot in the system
 * \param plot Plot to be registered
 */
int FoodSystem::Register(Plot* plot)
{
    (*plot).Register(new Food(plot));
    BaseSystem::Register(plot);
    return Cost();
}

/**
 * \brief Updates food system. Tally scores for food plots
 */
void FoodSystem::Update()
{
}

float FoodSystem::GetSatisfaction() const
{
    const float overloadedPenalty = 0.02f;
    float overloadedTally = 0;
    float earnedMoney = 0;
    for (auto&& plot : plots)
    {
        const auto food = dynamic_cast<Food*>(plot->GetPlotType());
        // If earnings exceeded operating costs, additional money is only worth half the score
        earnedMoney += food->earnedMoney - (food->earnedMoney - Clamp(food->earnedMoney, 0, OPERATING_COST)) * 0.5f;
        overloadedTally += food->overloadedTally;
    }
    earnedMoney /= plots.Count();
    float satisfaction = 1.f - float(OPERATING_COST - earnedMoney) / float(OPERATING_COST);
    
    overloadedTally = overloadedTally / plots.Count() * overloadedPenalty;
    satisfaction -= overloadedTally;
    
    satisfaction = Clamp(satisfaction, 0.f, 1.f);
    return satisfaction;
}

std::string FoodSystem::ContentString()
{ 
    float overloadedTally = 0;
    float earnedMoney = 0;
    for (auto&& plot : plots)
    {
        const auto food = dynamic_cast<Food*>(plot->GetPlotType());
        // If earnings exceeded operating costs, additional money is only worth half the score
        earnedMoney += food->earnedMoney - (food->earnedMoney - Clamp(food->earnedMoney, 0, OPERATING_COST)) * 0.5f;
        overloadedTally += food->overloadedTally > 0 ? 1 : 0;
    }
    std::stringstream ss;
    int lineCount = 0;
    if (overloadedTally > float(plots.Count()) / 8)
    {
        ss << "Build more restuarant" << std::endl << "to handle everyone" << std::endl;
        lineCount += 2;
    }
    if (float(OPERATING_COST - earnedMoney) / float(OPERATING_COST) > 0.1f)
    {
        ss << "Restuarants aren't" << std::endl << "earning enough money" << std::endl;
        lineCount += 2;
    }
    for (int i = 0; i < 4 - lineCount; ++i)
    {
        ss << std::endl;
    }
    ss << "Overloaded Count: " << overloadedTally << std::endl;
    ss << "Total Earnings:  $" << int(earnedMoney) << std::endl;
    ss << "Build Cost:      $" << Cost();
    return ss.str();
}

