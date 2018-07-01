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
    sf::CircleShape& UpdateShape();
    const Coordinate& Coords() const { return coords; }
    Base* const& GetPlotType() const { return currentType; }
    int GetOccupantCount() const { return occupants.Count(); }
    
    void Register(Base* base);
    void Enter(Citizen* citizen);
    void Leave(Citizen* citizen);
    void NewDay();
    void EndDay();
	void GenerateRoads();
    void Destroy();
    
	Road* GetRoad(Plot* nextPlot);
    bool IsRiver() const { return river; }
    
    void MarkAsRiver() { river = true; };
private:
    Coordinate coords;
    ScreenCoordinate sCoords{};
    float size;
    sf::CircleShape shape;
    Base* currentType;
    
    List<Citizen*> occupants;
	List<Road*> roads;
    int quadrant;
    bool river;
};

