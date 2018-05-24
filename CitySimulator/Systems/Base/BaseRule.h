#pragma once
#include "../../Helpers/Time.h"

class Plot;
class Citizen;
class BaseRule
{
public:
    BaseRule(Citizen& citizen) : citizen(&citizen) {};
    virtual ~BaseRule() = default;
    
    virtual float CalculateScore() = 0;
    virtual bool FindPlot() = 0;
    virtual void EnterPlot(Plot* plot) = 0;
    virtual void LeavePlot(Plot* plot) = 0;
    virtual void Update() = 0;
protected:
    helper::Time lastUpdate;
    Citizen* citizen;
};

