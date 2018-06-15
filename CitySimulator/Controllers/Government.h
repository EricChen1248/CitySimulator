#pragma once
class Government
{
public:
    
    static void AddTax(const float money) { taxDollars += money; };
    static float TaxDollars() { return taxDollars; }
    static int NewChildren(int adultCount);
private:
    static float taxDollars;
    static float birthRate;
};

