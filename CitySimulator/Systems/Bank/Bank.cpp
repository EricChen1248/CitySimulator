#include "Bank.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"

Bank::Bank(Plot* plot) : Base(plot, BANK)
{
	cost = CoreController::RandomInt(50, 100);
	administrationFee = CoreController::RandomInt(0, 100);
	transactionCost = CoreController::RandomInt(0, 100);
	score = 0;
	color = BANK_COLOR;
}

/**
* \brief Reset's Food Plot (score to 0)
*/
void Bank::EndDay()
{
	score = 0;
}


/**
* \brief New entry ( +score )
*/
void Bank::Enter()
{
	//Need to revise
	score += cost;
}