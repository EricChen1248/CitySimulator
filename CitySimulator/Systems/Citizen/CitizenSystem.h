#pragma once
#include "Citizen.h"
#include "../../Collections/List.h"

class CitizenSystem
{
public:
    CitizenSystem();
    ~CitizenSystem();
    void Update() const;
    void Render() const;
    void RenderInterday() const;
    void PruneDead();
private:
    List<Citizen*> citizens;
    int citizenCount;
};

