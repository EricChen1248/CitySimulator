#include "Bank.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Government.h"
#include "../../Helpers/HelperFunctions.h"


Bank::Bank(Plot* plot) : Base(plot, BANK)
{
    cost = 6000;
    administrationFee = RandomInt(1, 100);
    transactionCost = RandomInt(50, 100);
    color = BANK_COLOR;
    customerPerDay = 0;
    earnedMoney = 0;
    countOfCustomerNow = 0;
}

std::string Bank::ContentString()
{
    std::stringstream ss;
    if (customerPerDay < 50)
        ss << "We should change" << std::endl << "locations, there aren't" << std::endl << "enough customers. ";
    else
        ss << "We are operating " << std::endl << "very well!" << std::endl << "This is a good spot!";
    ss << std::endl << std::endl;
    ss << "Today's customer: " << customerPerDay << std::endl;
    ss << "Today's earnings:$" << earnedMoney;
    return ss.str();
}

/**
* \brief Reset's Bank Plot (score to 0) and resets bank's acuumulated customer to zero
*/
void Bank::NewDay()
{
    customerPerDay = 0;
    earnedMoney = 0;
}

/**
* \brief New entry ( +score )
*/
void Bank::Enter()
{
    ++customerPerDay;
    Government::AddTax(transactionCost * 0.5f);
}
