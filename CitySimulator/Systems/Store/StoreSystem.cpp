#include "StoreSystem.h"
#include "Store.h"
#include "StoreRule.h"
#include "../../Helpers/HelperFunctions.h"


class StoreRule;

StoreSystem::StoreSystem() : BaseSystem(STORE)
{
}


StoreSystem::~StoreSystem() = default;

/**
* \brief Registers a new Store plot in the system
* \param plot Plot to be registered
*/
int StoreSystem::Register(Plot* plot)
{
	(*plot).Register(new Store(plot));
	BaseSystem::Register(plot);
    return 0;
}

/**
* \brief Updates Store system.
*/
void StoreSystem::Update()
{
    // DO NOTHING
}

/**
* \brief Resets the day (clears log & resets plots)
*/
void StoreSystem::EndDay()
{
	for (auto && plot : plots)
	{
		plot->GetPlotType()->EndDay();
	}
}

float StoreSystem::GetSatisfaction() const
{
    float earnings = 0;
    float costs = 0;
    for (auto && plot : plots)
    {
        const auto store = dynamic_cast<Store*>(plot->GetPlotType());
        earnings += store->earnings;
        costs += Store::OPERATING_COST + store->cleaningCost;
    }
    return Clamp(1 - (costs - earnings) / costs, 0.f, 1.f);
}

void StoreSystem::NewDay()
{
    for (auto && plot : plots)
    {
        plot->GetPlotType()->NewDay();
    }
}

std::string StoreSystem::ContentString()
{
    float earnings = 0;
    float costs = 0;
    for (auto && plot : plots)
    {
        const auto store = dynamic_cast<Store*>(plot->GetPlotType());
        earnings += store->earnings;
        costs += Store::OPERATING_COST + store->cleaningCost;
    }
    std::stringstream ss;
    
    int lineCount;
    if (earnings > costs)
    {
        ss << "The stores are earning" << std::endl << "enough money"<< std::endl;
        lineCount = 2;
    }
    else
    {
        ss << "We aren't earning" << std::endl << "enough money. ";
        if (costs - plots.Count() * Store::OPERATING_COST > 0)
        {
            ss << "Maybe"  << std::endl << "we're spending too much"  << std::endl << "on cleaning?"<< std::endl;   
        }
        else
        {
            ss << "Maybe"  << std::endl << "we has too many"  << std::endl << "stores?"<< std::endl;  
        }
        lineCount = 4;
    }
    for (int i = 0; i < 6 - lineCount; ++i)
    {
        ss << std::endl;
    }
    ss << "Total Earnings: $" << earnings << std::endl;
    ss << "Total Costs:    $" << costs << std::endl;
    return ss.str();
}
