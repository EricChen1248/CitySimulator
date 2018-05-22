#pragma once
#include "../../Collections/List.h"
#include "../SystemEnum.h"
#include "../Plot/Plot.h"

class BaseSystem
{
public:
    System SystemType;
    
    BaseSystem(const System system) : SystemType(system) {};

    const List<Plot*>& Plots() const { return plots; }

    virtual ~BaseSystem() = default;
    
    virtual void Update(float deltaTime) = 0;
    
    virtual void Register(Plot* plot);
    virtual void Unregister(Plot* plot);
protected:
    List<Plot*> plots;
};

inline void BaseSystem::Register(Plot* plot)
{
    plots.InsertLast(plot);
}

inline void BaseSystem::Unregister(Plot* plot)
{
    plots.Remove(plot);
}

