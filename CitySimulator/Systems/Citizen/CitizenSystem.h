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
    void PruneDead();
	void ResetDay();
	void CalculateSatisfaction() const;
    const List<Citizen*>& Citizens() const { return citizens; }
private:
    List<Citizen*> citizens;
    int citizenCount;
};

