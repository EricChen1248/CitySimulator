#pragma once
class Government
{
public:
    static void AddTax(const float money) { taxDollars += money; }
    static void ChangeBirthRate(const float rate) { birthRate = rate; }
    static float TaxDollars() { return taxDollars; }
    static float BirthRate() { return birthRate; }
private:
    static float taxDollars;
    static float birthRate;
};

