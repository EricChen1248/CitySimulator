#pragma once
#include "Line.hpp"

class Plot;
class Road
{
public:
	Road(Plot* plotOne, Plot* plotTwo);
	~Road();
    static const int MAX_SPEED = 3;
	//Getter
	float Speed() const;
	bool IsRiver() const;
    Line& Shape() { return shape; }

	//Setter
	int LevelUp();
	int Repair();
    int Cost() const;
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
    
    const int upgradeCosts[11] { 5000,200,300,400,500,600,700,800,900,1000, 2147483647};
    const float baseLifeSpan = 20.f;
	
    float lifespan{};
	bool isBroken;
	bool isRiver;
};

