#pragma once
#include "../../Helpers/Time.h"

class Citizen;
class BaseRule
{
public:
    BaseRule(Citizen& citizen) : citizen(&citizen) {};
    virtual ~BaseRule() = default;
    
    virtual float CalculateScore() = 0;
    virtual void EnterPlot() = 0;
    virtual void LeavePlot() = 0;
protected:
    helper::Time lastUpdate;
    Citizen* citizen;
};

