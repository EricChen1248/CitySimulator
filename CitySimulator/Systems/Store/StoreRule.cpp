#include "StoreRule.h"



StoreRule::StoreRule(Citizen& citizen) : BaseRule(citizen, STORE)
{
    
}


StoreRule::~StoreRule()
= default;

float StoreRule::CalculateScore()
{
    return 0;
}

bool StoreRule::FindPlot()
{
    return true;
}

void StoreRule::EnterPlot(Plot* plot)
{
}

void StoreRule::LeavePlot(Plot* plot)
{
}

void StoreRule::Update()
{
}

bool StoreRule::IsSatisfied()
{
    return true;
}
