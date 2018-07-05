#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "../Base/BaseRule.h"
#include "../Plot/Plot.h"
#include "../../Helpers/Coordinate.h"
#include "../../Collections/List.h"
#include "../../Collections/Stack.h"
#include "../Citizen/CitizenEnum.h"
/**
 * \brief The central entity of our game/simulation
 */

class BaseRule;

class Citizen
{
public:
    Citizen(Plot* plot);
    Citizen(Plot* plot, Citizen* parent1, Citizen* parent2);
    ~Citizen();
    
    sf::CircleShape& GetShape() { return shape; }
    const Coordinate& Coords() const { return coords; }
    int GetMoney() const { return money;}
    
    bool IncreaseMoney(int m);
    void SetActiveRule(BaseRule* rule) { activeRule = rule; }
    void SetTarget(Plot* t);

    void Update();
    void UpdateScreenCoordinates();
    
    void Wait(float time);
    void NewDay();
    void EndDay();
    
    void DoubleSpeed() { doubleSpeedTime = 24.f; };
    
    BaseRule* FindRule(System system);
    void ForceRule(System ruleType, float waitTime = 0);
    
	// LifeCycle function
    int Age() const { return age; }
	Gender GetGender() const { return gender; }
	Citizen* GetFamilyMember(const Family character) const { return family[static_cast<int>(character)]; }
	bool IsMarried() const;
    bool IsDead() const { return dead; }
    
	void Marry(Citizen* spouse);
	void Die();
    
private:
    void FindNextTarget();
    void GenRules();
    void FindRandomTarget();
    void UpdateRules() const;
    void FindPath();

	void SetFamily(const Family& character, Citizen* citizen);
    // Collections
    List<BaseRule*> rules;
    Stack<Coordinate>* path{};
    
    // Rule properties
    Plot* target;
    Plot* currentPlot;
    Road* currentRoad;
    BaseRule* activeRule;
    
	static const int FAMILY_NUM = 3;
    
    // Entity Properties
    int money;
    
    Coordinate tempTarget;
    Coordinate coords;
    float moveSpeed;
    float doubleSpeedTime;
    
    float waitTime;
    bool inPlot;
    bool pathFindFailed;
    
    bool dead;
    int age;
	Gender gender;
	Citizen* family[FAMILY_NUM] {nullptr};
    
    sf::CircleShape shape;
};
