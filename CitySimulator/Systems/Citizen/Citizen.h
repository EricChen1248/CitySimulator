#pragma once
#include "../../Helpers/Coordinate.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../Plot/Plot.h"

class Citizen
{
public:
    Citizen();
    ~Citizen();
    void Update(float deltaTime);
    sf::CircleShape GetShape() const;
private:
    Coordinate coords;
    Plot* target;
    float moveSpeed;
};

