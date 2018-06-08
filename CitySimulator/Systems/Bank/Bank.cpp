#include "Bank.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"

Bank::Bank(Plot* plot) : Base(plot, BANK)
{
	cost = CoreController::RandomInt(50, 100);
	administration_fee = CoreController::RandomInt(0, 100);
	transaction_cost = CoreController::RandomInt(0, 100);
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
	score += cost;
}
