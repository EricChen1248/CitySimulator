#pragma once
#include "../../Helpers/Coordinate.h"
#include "../../Helpers/Road.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../Base/Base.h"
#include "../../Collections/List.h"
#include "../Citizen/Citizen.h"

class Base;
class Citizen;
class Road;

/**
 * \brief Container class for each city plot
 */
class Plot
{
    friend class PlotSystem;
public:
    Plot(int x, int y, int z);
    ~Plot();
    sf::CircleShape& GetShape() { return shape; }
    const Coordinate& Coords() const { return coords; }
    Base* const& GetPlotType() const { return currentType; }
    int GetOccupantCount() const { return occupantCount; }
    
    void Register(Base* base);
    void Enter(Citizen* citizen);
    void Leave(Citizen* citizen);
    
    void NewDay() const;
    void EndDay() const;
    void Destroy();
	
	void InsertNewRoad(Road* newRoad, int i) const;
	Road* GetRoad(int i) const;
    Road* GetRoad(Plot* plot) const;
    
    bool IsRiver() const { return river; }
    void BuiltBridge();
    void MarkNotRiver();
	void MarkAsRiver();
private:
    Coordinate coords;
    float size = 10.f;
    sf::CircleShape shape;
    Base* currentType;
    
    int occupantCount = 0;
	List<Road*> roads;
    int quadrant = 0;
    bool river = false;
};

