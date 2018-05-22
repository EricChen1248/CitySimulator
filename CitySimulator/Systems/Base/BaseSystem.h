#pragma once
#include "Base.h"
#include "../../Collections/List.h"
#include "../SystemEnum.h"

class BaseSystem
{
public:
    System SystemType;
    
    BaseSystem(const System system) : SystemType(system) {};
    virtual ~BaseSystem() = default;
    
    virtual void Update(float deltaTime) = 0;
    
    void Register(Plot* plot);
    void Unregister(Plot* plot);
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

