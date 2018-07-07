#pragma once

/**
 * \brief Handles and stores user variables
 */
class Government
{
public:
    static void AddTax(float money);
    static void ChangeBirthRate(float rate);
    static float TaxDollars();
    static float BirthRate();
private:
    static float taxDollars;
    static float birthRate;
};

