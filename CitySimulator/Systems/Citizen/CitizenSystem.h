#pragma once
#include "Citizen.h"
#include "../../Collections/List.h"

class CitizenSystem
{
public:
    CitizenSystem();
    ~CitizenSystem();
    void Update(const float deltaTime);
    void Render();
private:
    List<Citizen*> citizens;
    int citizenCount;
};

