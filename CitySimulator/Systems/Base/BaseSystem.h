#pragma once
#include "../../Collections/List.h"
#include "../SystemEnum.h"
#include "../Plot/Plot.h"
#include "../../Log.h"

class BaseSystem
{
public:
    System SystemType;
    
    BaseSystem(const System system) : SystemType(system), score(0) {};

    const List<Plot*>& Plots() const { return plots; }
    int GetScore() const { return score; }
    virtual ~BaseSystem() = default;
    
    virtual void Update(float deltaTime) = 0;
    virtual void LogSatisfied(Citizen* citizen, BaseRule* rule) = 0;
    virtual void LogUnsatisfied(Citizen* citizen, BaseRule* rule) = 0; 
    virtual void Register(Plot* plot);
    virtual void Unregister(Plot* plot);
    virtual void ResetDay();
protected:
    List<Plot*> plots;
    List<Log*> satisfiedLog;
    List<Log*> unsatisfiedLog;
    
    int score;
};

inline void BaseSystem::Register(Plot* plot)
{
    plots.InsertLast(plot);
}

inline void BaseSystem::Unregister(Plot* plot)
{
    plots.Remove(plot);
}

inline void BaseSystem::ResetDay()
{
    satisfiedLog.Dispose();
    unsatisfiedLog.Dispose();
}

