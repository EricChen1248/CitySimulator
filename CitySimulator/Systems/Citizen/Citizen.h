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
enum Family
{
	Father = 0,
	Mother,
	Child,
	Spouse,
};

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
    void NewDay();
    void EndDay();
    void ForceRule(System ruleType, float waitTime = 0);
    BaseRule* FindRule(System system);
	//LifeCycle function
	void MarrySomeOne(Citizen* spouse);
	void GiveBirth(Citizen* child);
	void Birth(Citizen* parent,Citizen* parent2);
	void Death();
private:
    void FindNextTarget();
    void GenRules();
    void FindRandomTarget();
    void UpdateRules() const;
    void FindPath();


	void setFamily(const Family& character, Citizen* citiz);
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
    bool pathFindFailed;
    //Family System
	bool gender;
	Citizen** family;
    // Misc Properties
    sf::CircleShape shape;
};
