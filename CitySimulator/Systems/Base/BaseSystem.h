#pragma once
#include "../../Collections/List.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/CustomExceptions.h"

#include "../SystemEnum.h"
#include "../Plot/Plot.h"

/**
 * \brief Abstract class that is the base of all systems
 */
class Log;
class BaseSystem
{
public:
    const System SystemType;
    
    BaseSystem(const System system) : SystemType(system) {};
    const List<Plot*>& Plots() const { return plots; }
    virtual float GetSatisfaction() const { return 0; }
    bool Toggleable() const { return toggleable; } 
    virtual ~BaseSystem();
    
    /**
     * \brief Virtual function handling the update events
     */
    virtual void Update() = 0;
    virtual int Register(Plot* plot);
    virtual void Unregister(Plot* plot);
    virtual void NewDay();
    virtual void EndDay();
    virtual int Cost() const { return 0; };
    virtual void Destroy(Plot* plot);
    virtual void Toggle() {};
    virtual std::string ContentString() { return ""; }
protected:
    List<Plot*> plots;
    bool toggleable = false;    
};


inline BaseSystem::~BaseSystem()
= default;

/**
 * \brief Register a plot into the system for quick lookup and updating
 * \param plot Plot to register in system
 */
inline int BaseSystem::Register(Plot* plot)
{
    plots.InsertLast(plot);
    return 0;
}

/**
 * \brief Unregister a plot to remove it from being tracked in the system
 * \param plot Plot to unregister in the system
 */
inline void BaseSystem::Unregister(Plot* plot)
{
    plots.Remove(plot);
}

inline void BaseSystem::NewDay()
{
    for (auto&& plot : plots)
    {
        plot->NewDay();
    }
}


/**
 * \brief Resets the system to a new day
 */
inline void BaseSystem::EndDay()
{
    for (auto && plot : plots)
    {
        plot->EndDay();
    }
}

inline void BaseSystem::Destroy(Plot* plot)
{
    if (SystemType != plot->GetPlotType()->SystemType)
    {
        std::stringstream ss;
        ss << "Attempting to destroy plot of type " << SYSTEM_NAMES[plot->GetPlotType()->SystemType] << " with a system of type " << SYSTEM_NAMES[SystemType];
        throw IncorrectSystemType(ss.str());
    }
    
    plot->Destroy();
    Unregister(plot);
}

