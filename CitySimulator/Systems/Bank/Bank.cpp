#include "Bank.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"

Bank::Bank(Plot* plot) : Base(plot, Bank)
{
	cost = CoreController::RandomInt(50, 100);
	earnings = 0;
	color = BANK_COLOR;
}

/**
* \brief Reset's Food Plot (earnings to 0)
*/
void Bank::Reset()
{
	earnings = 0;
}


/**
* \brief New entry ( +earnings )
*/
void Bank::Enter()
{
	earnings += cost;
}
