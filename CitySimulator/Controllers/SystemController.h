#pragma once

#include "../Systems/Plot/PlotSystem.h"
#include "../Systems/Citizen/CitizenSystem.h"
#include "../Systems/Base/BaseSystem.h"
class PlotSystem;

class SystemController
{
public:
    SystemController();
    ~SystemController();
    void Initialize();
    void Update(float deltaTime);
    void Render() const;


    PlotSystem* Plots() const { return plots; }
    CitizenSystem* Citizens() const { return citizens; }

private:
    PlotSystem* plots{};
    CitizenSystem* citizens{};
    
    List<BaseSystem*> systems;
};
