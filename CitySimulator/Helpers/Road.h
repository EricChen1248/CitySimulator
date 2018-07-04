#pragma once
#include "Line.hpp"

class Plot;
class Road
{
public:
	Road(Plot* plotOne, Plot* plotTwo);
	~Road();
    static const int MAX_SPEED = 10;
	//Getter
	float Speed() const;
	bool IsRiver() const;
    Line& Shape() { return shape; }

	//Setter
	int LevelUp();
	int Repair();
	void MarkAsRiver();

	//Function
	int PerformClick();
	void Enter();
	void Leave();
	bool IsRoad(const Plot* plotOne, const Plot* plotTwo) const;
	void EndDay();
	void Render() const;
    
    std::string ContentString() const;
    std::string ButtonString() const;
    bool InSimpleBounds(const float x, const float y) const { return shape.InSimpleBounds(x, y); }
    bool InComplexBounds(const float x, const float y) const { return shape.InComplexBounds(x, y); }
    
private:
	Line shape;
	Plot* plotOne;
	Plot* plotTwo;
    
	int level;
	int capacity;
	int citizenCount;
    
    // TODO : Set road repair costs and update costs
    const int repairCost = 100;
    const int upgradeCosts[10] { 10,20,30,40,50,60,70,80,90,100};
	
    float lifespan{};
	bool isBroken;
	bool isRiver;
};

