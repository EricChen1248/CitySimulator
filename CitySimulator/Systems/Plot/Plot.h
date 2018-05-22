#pragma once
#include "../../Helpers/Coordinate.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../Base/Base.h"
#include "../../Collections/List.h"
#include "../Citizen/Citizen.h"

class Base;
class Citizen;

/**
 * \brief Container class for each city plot
 */
class Plot
{
public:
    Plot(int x, int y, int z);
    ~Plot();
    sf::CircleShape& GetShape();
    const Coordinate& Coords() const { return coords; }
    Base* const& GetPlotType() const { return currentType; }
    int GetOccupantCount() { return occupants.Count(); }
    
    void Register(Base* base);
    void Enter(Citizen* citizen);
    void Leave(Citizen* citizen);
private:
    Coordinate coords;
    ScreenCoordinate sCoords{};
    float size;
    sf::CircleShape shape;
    Base* currentType;
    
    List<Citizen*> occupants;
};

