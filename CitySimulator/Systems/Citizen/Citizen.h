#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "../Base/BaseRule.h"
#include "../Plot/Plot.h"
#include "../../Helpers/Coordinate.h"
#include "../../Collections/List.h"
#include "../../Collections/Stack.h"

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
    sf::CircleShape& GetShape() { return shape; }
    const Coordinate& Coords() const { return coords; }
    const int& GetMoney() const { return money;}
    const bool& InPlot() const { return inPlot; }
    const int& Age() const { return age; }
    const bool& IsDead() const { return dead; }

    // Setters
    bool IncreaseMoney(int m);
    void SetActiveRule(BaseRule* rule) { activeRule = rule; }
    void SetTarget(Plot* t);

    void Update();
    void UpdateScreenCoordinates();
    void Wait(float time);
    void EndDay();
    void ForceRule(System ruleType, float waitTime = 0);
    BaseRule* FindRule(System system);
    void Death();
private:
    void FindNextTarget();
    void GenRules();
    void FindRandomTarget();
    void UpdateRules() const;
    void FindPath();
    
    // Collections
    List<BaseRule*> rules;
    Stack<Coordinate>* path{};
    
    // Rule properties
    Plot* target;
    Plot* currentPlot;
    BaseRule* activeRule;
    
    // Entity Properties
    Coordinate tempTarget;
    Coordinate coords;
    float moveSpeed;
    int money;
    int unsatisfiedCount{};
    float waitTime;
    bool inPlot;
    bool dead;
    int age;
    
    // Misc Properties
    sf::CircleShape shape;
};

