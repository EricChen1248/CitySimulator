#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "../Plot/Plot.h"
#include "../Base/BaseRule.h"
#include "../Citizen/CitizenEnum.h"
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
	Citizen* GetFamilyMember(const Relationship relation) const { return family[static_cast<int>(relation)]; }
	bool IsMarried() const;
    bool IsDead() const { return dead; }
    
	void Marry(Citizen* spouse);
	void Die();
    void DeathEvents();
    
private:
    void FindNextTarget();
    void GenRules();
    void FindRandomTarget();
    void UpdateRules() const;
    void FindPath();

	void SetRelationships(const Relationship& relation, Citizen* citizen);
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
	List<Citizen*> descendants;
    sf::CircleShape shape;
};
