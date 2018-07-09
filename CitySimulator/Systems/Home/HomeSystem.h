#pragma once
#include "../Base/BaseSystem.h"

/**
* \brief Home systems that tracks and handles collective home plots and events
*/

class HomeSystem :
	public BaseSystem
{
public:
	HomeSystem();
	~HomeSystem();
	int Register(Plot* plot) override;
    int Cost() const override { return 10000; };  
	void Update() override;
	float GetSatisfaction() const override;
	void EndDay() override;
    void NewDay() override;
    int FamilyCount() const { return familyCount; };
	std::string ContentString()override;
private:
	void CalculateTotalFamily();
    
    int familyCount = 0;

};

