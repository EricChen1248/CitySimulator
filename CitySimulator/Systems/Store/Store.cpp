#include "Store.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"


Store::Store(Plot* plot) : Base(plot, STORE)
{
	cost = RandomInt(10, 1000);
	score = 0;
    color = STORE_COLOR;
}

Store::~Store()
= default;


/**
* \brief EndDay's Store Plot (score to 0)
*/
void Store::EndDay()
{
	score = -RandomInt(1, 50);
}


/**
* \brief New entry ( +score )
*/
void Store::Enter()
{
	score += cost;
}

