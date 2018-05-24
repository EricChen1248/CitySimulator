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
    Citizen(Plot* plot);
    ~Citizen();
    
    // Getters
    sf::CircleShape& GetShape();
    const Coordinate& Coords() const { return coords; }
    const int& GetMoney() const { return money;}
    const bool& InPlot() const { return inPlot; }

    // Setters
    bool IncreaseMoney(int m);
    void SetActiveRule(BaseRule* rule) { activeRule = rule; }
    void SetTarget(Plot* t);

    void Update();  
    void Wait(float time);
private:
    void FindNextTarget();
    void GenRules();
    void FindRandomTarget();
    void UpdateRules() const;
    
    // Collections
    List<BaseRule*> rules;
    
    // Rule properties
    Plot* target;
    Plot* currentPlot;
    BaseRule* activeRule;
    
    // Entity Properties
    Coordinate coords;
    float moveSpeed;
    int money;
    int unsatisfiedCount{};
    float waitTime;
    bool inPlot;
    
    // Misc Properties
    sf::CircleShape shape;
};
