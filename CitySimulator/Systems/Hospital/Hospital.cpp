#include "Hospital.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/Government.h"

Hospital::Hospital(Plot* plot) : Base(plot, HOSPITAL)
{
	// TODO : cost
    cost = RandomInt(50, 100);
    score = 0;
    color = HOSPITAL_COLOR;
}

/**
 * \brief EndDay's Hospital Plot (score to 0)
 */
void Hospital::EndDay()
{
    score = -50;
}


/**
 * \brief New entry ( +score )
 */
void Hospital::Enter()
{
    score += cost;
    Government::AddTax(cost * 0.1f);
}
