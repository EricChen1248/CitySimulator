#pragma once

#include "../Systems/Systems.h"
#include "../Systems/SystemEnum.h"

#include "../Collections/List.h"
#include "../Collections/LinkedList.h"

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
    void ResetDay();
    int SystemCount() const;
    const LinkedList<Citizen*>& GetCitizens() const;

    BaseSystem* GetSystem(System system) const;
    const List<BaseSystem*>& GetSystems() const { return systems; };
	

    PlotSystem* Plots() const { return plots; }
    CitizenSystem* Citizens() const { return citizens; }
	River* Rivers() const { return river; }
    
private:
	float timeSinceUpdate;
    PlotSystem* plots{};
    CitizenSystem* citizens{};
    List<BaseSystem*> systems{};
    River* river;
};

