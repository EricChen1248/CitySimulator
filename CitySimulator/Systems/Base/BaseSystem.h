#pragma once
#include "../../Collections/List.h"
#include "../SystemEnum.h"
#include "../Plot/Plot.h"
#include "../../Log.h"

/**
 * \brief Abstract class that is the base of all systems
 */
class BaseSystem
{
public:
    System SystemType;
    
    BaseSystem(const System system) : SystemType(system), score(0) {};

    const List<Plot*>& Plots() const { return plots; }
    float GetScore() const { return score; }
    List<Log*> SatisfiedLog() const { return satisfiedLog; }
    List<Log*> UnsatisfiedLog() const { return unsatisfiedLog; }
    virtual ~BaseSystem() = default;
    
    
    /**
     * \brief Virtual function handling the update events
     */
    virtual void Update() = 0;
    virtual void LogSatisfied(Citizen* citizen, BaseRule* rule) = 0;
    virtual void LogUnsatisfied(Citizen* citizen, BaseRule* rule) = 0; 
    virtual void Register(Plot* plot);
    virtual void Unregister(Plot* plot);
    virtual void ResetDay();
protected:
    List<Plot*> plots;
    List<Log*> satisfiedLog;
    List<Log*> unsatisfiedLog;
    
    float score;
};


/**
 * \brief Register a plot into the system for quick lookup and updating
 * \param plot Plot to register in system
 */
inline void BaseSystem::Register(Plot* plot)
{
    plots.InsertLast(plot);
}

/**
 * \brief Unregister a plot to remove it from being tracked in the system
 * \param plot Plot to unregister in the system
 */
inline void BaseSystem::Unregister(Plot* plot)
{
    plots.Remove(plot);
}



/**
 * \brief Resets the system to a new day
 */
inline void BaseSystem::ResetDay()
{
    score = 0;
    satisfiedLog.Dispose();
    unsatisfiedLog.Dispose();
}

