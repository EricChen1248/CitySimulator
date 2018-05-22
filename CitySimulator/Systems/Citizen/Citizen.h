#pragma once
#include "../../Helpers/Coordinate.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../Plot/Plot.h"

/**
 * \brief The central entity of our game/simulation
 */
class Citizen
{
public:
    Citizen(Coordinate coords);
    ~Citizen();
    void Update(float deltaTime);
    sf::CircleShape& GetShape();
private:
    Coordinate coords;
    Plot* target;
    float moveSpeed;
    sf::CircleShape shape;
};

