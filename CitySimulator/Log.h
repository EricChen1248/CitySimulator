#pragma once
#include "Systems/Citizen/Citizen.h"

struct Log
{
    Log(const Coordinate& coords, BaseRule* rule, Citizen* citizen);
    ~Log() { delete Rule; };
    
    Citizen* Citizen;
    Coordinate Coords;
    helper::Time Time;
    BaseRule* Rule;
};

