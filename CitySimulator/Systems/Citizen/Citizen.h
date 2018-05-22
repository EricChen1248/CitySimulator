#pragma once
#include "../../Helpers/Coordinate.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "../Plot/Plot.h"
#include "../../Collections/List.h"
#include "../Base/BaseRule.h"

/**
 * \brief The central entity of our game/simulation
 */
class BaseRule;

class Citizen
{
public:
    Citizen(const Coordinate& coords);
    ~Citizen();
    void Update(float deltaTime);
    sf::CircleShape& GetShape();
    
    int Money;
private:
    void FindNextTarget();
    Coordinate coords;
    Plot* target;
    float moveSpeed;
    sf::CircleShape shape;
    List<BaseRule*> rules;
};
