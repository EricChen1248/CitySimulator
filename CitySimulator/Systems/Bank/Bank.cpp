#include "Bank.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"
Bank::Bank(Plot* plot) : Base(plot, BANK)
{
	cost = 1000;
	administrationFee = RandomInt(1, 100);
	transactionCost = RandomInt(1, 100);
	score = 0;
	color = BANK_COLOR;
	customerPerDay = 0;
	earnedMoeny = 0;
	countOfCustomerNow = 0;
}

std::string Bank::ContentString()
{
	std::stringstream ss;
	if (customerPerDay < 50)
		ss << "We should change" << std::endl << "location, there aren't" << std::endl << "enough customers. ";
	else
		ss << "We are operating "<<std::endl<< "very well!" << std::endl << "This is a good spot!";
	ss << std::endl << std::endl;
	ss << "Today Customer: " << customerPerDay << std::endl;
	ss << "Today earning: " << earnedMoeny;
	return ss.str();
}
/**
* \brief Reset's Bank Plot (score to 0)
and reset bank's acuumulated customer to zero
*/
void Bank::NewDay()
{
	customerPerDay = 0;
	earnedMoeny = 0;
	score = 0;
}


void Bank::EndDay()
{
}


/**
* \brief New entry ( +score )
*/
void Bank::Enter()
{
	//Need to revise
	++customerPerDay;
	Government::AddTax(transactionCost*0.5f);
}