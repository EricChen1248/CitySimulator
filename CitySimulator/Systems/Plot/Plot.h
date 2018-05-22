#pragma once
#include "../../Helpers/Coordinate.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../Base/Base.h"

class Base;

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

private:
    Coordinate coords;
    ScreenCoordinate sCoords{};
    float size;
    sf::CircleShape shape;
    Base* currentType;
};

