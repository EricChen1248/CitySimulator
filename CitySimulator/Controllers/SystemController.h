#pragma once

#include "../Systems/Plot/PlotSystem.h"
#include "../Systems/Citizen/CitizenSystem.h"
#include "../Systems/Base/BaseSystem.h"
class PlotSystem;

/**
 * \brief Stores all systems and handles interfacing
 */
class SystemController
{
public:
    SystemController();
    ~SystemController();
    void Initialize();
    void Update() const;
    void Render() const;
    void RenderInterday() const;
    void AdvanceDay() const;
	void UpdateBewtweenDay();
    BaseSystem* GetSystem(System system) const;
    const List<BaseSystem*>& GetSystems() const { return systems;};


    PlotSystem* Plots() const { return plots; }
    CitizenSystem* Citizens() const { return citizens; }

private:
    PlotSystem* plots{};
    CitizenSystem* citizens{};
    List<BaseSystem*> systems{};
};

