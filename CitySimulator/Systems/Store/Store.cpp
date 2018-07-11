#include "Store.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"

const int Store::CROWDED = 30;
const int Store::OPERATING_COST = 2000;

Store::Store(Plot* plot) : Base(plot, STORE)
{
    cost = 8000;
    color = STORE_COLOR;
}

Store::~Store()
= default;

/**
* \brief EndDay's Store Plot (score to 0)
*/
void Store::EndDay()
{
    Government::AddTax(float(-Clamp(OPERATING_COST + cleaningCost - earnings, 0)));
}

void Store::NewDay()
{
    mostCustomer = 0;
    crowdedCount = 0;
    earnings = 0;
    cleaningCost = 0;
}
std::string Store::ContentString()
{
    std::stringstream ss;
    int lineCount = 0;
    if (crowdedCount > 0)
    {
        ss << "Too many people! We" << std::endl << "spent extra on cleaning" << std::endl;
        lineCount += 2;
    }
    if (earnings < OPERATING_COST)
    {
        ss << "We aren't making" << std::endl << "enough money!" << std::endl;
        lineCount += 2;
    }
    if (lineCount == 0)
    {
        ss << "Everything was" << std::endl << "A-OK today~" << std::endl;
        lineCount += 2;
    }
    for (int i = 0; i < 4 - lineCount; ++i)
    {
        ss << std::endl;
    }
    
    ss << "Most customer:   " << mostCustomer << std::endl;
    ss << "Was overcrowded: " << crowdedCount << std::endl;
    ss << "Earnings:       $" << earnings << std::endl;
    ss << "Operating Cost: $" << OPERATING_COST + cleaningCost;
    return ss.str();
}

void Store::Enter()
{
    if (plot->GetOccupantCount() > CROWDED)
    {
        ++crowdedCount;
        // Cleaning cost
        cleaningCost += 200;
    }
    mostCustomer = Max(mostCustomer, plot->GetOccupantCount());
}

void Store::Payment(const float money)
{
    earnings += int(money * 0.5);
    Government::AddTax(money * 0.1f);
}
