#pragma once
#include "../../Helpers/Coordinate.h"
#include <SFML/Graphics/CircleShape.hpp>

class Plot
{
public:
    Plot(int x, int y, int z);
    ~Plot();
    sf::CircleShape GetShape() const;
private:
    Coordinate coords;
    
    int size;
    
};

