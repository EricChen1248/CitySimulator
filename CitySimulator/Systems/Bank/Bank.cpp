#include "Bank.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"

Bank::Bank(Plot* plot) : Base(plot, BANK)
{
	cost = CoreController::RandomInt(50, 100);
	score = 0;
	color = BANK_COLOR;
}

/**
* \brief EndDay's Food Plot (score to 0)
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
