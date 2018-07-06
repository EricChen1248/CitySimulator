#pragma once
class DisasterController
{
public:
	DisasterController();
	~DisasterController();
	void Update();
private:
	void Apocalypse();
	void Earthquake();
	void Hurricane();
	void Tsunami();	
	void WildFire();
	
	void MajestysMarvel();
	void AngelsAegis();
	void GodsGift();
    
    void earthquake();
    
    
    float shakeTime = 0.f;
    void (DisasterController::*funct)();
};

