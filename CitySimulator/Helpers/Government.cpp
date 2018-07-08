#include "Government.h"


float Government::taxDollars = 0.f;
float Government::birthRate = 0.3f;

/**
 * \brief Adds money to the user's money
 * \param money Amount of money to add
 */
void Government::AddTax(const float money)
{
    taxDollars += money;
}
/**
 * \brief Changes the birthrate of the citizens
 * \param rate Current birthrate
 */
void Government::ChangeBirthRate(const float rate)
{
    birthRate = rate;
}

float Government::TaxDollars()
{
    return taxDollars;
}

float Government::BirthRate()
{
    return birthRate;
}
