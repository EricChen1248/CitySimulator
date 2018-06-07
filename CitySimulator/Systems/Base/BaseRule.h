#pragma once
#include "../../Helpers/Time.h"

class Plot;
class Citizen;
/**
 * \brief Abstract class that is the base of all system rules
 */
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
    virtual bool IsSatisfied() = 0;
    virtual void EndDay() {};
protected:
    helper::Time lastUpdate;
    Citizen* citizen;
};

