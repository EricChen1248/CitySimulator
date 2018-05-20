#pragma once
#include "../../Helpers/Coordinate.h"
#include <SFML/Graphics/CircleShape.hpp>

/**
 * \brief Container class for each city plot
 */
class Plot
{
public:
    Plot(int x, int y, int z);
    ~Plot();
    sf::CircleShape GetShape() const;

    const Coordinate& Coords() const { return coords; }

    bool hasCoords(Coordinate coord) const;
private:
    Coordinate coords;
    
    float size;
    
};

