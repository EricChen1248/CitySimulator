#include "StoreRule.h"
#include "Store.h"
#include "StoreSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../Food/FoodRule.hpp"
#include "../Home/HomeRule.h"

const float StoreRule::MAX_STOCK = 800.f;
const float StoreRule::RESTOCK = 100.f;

const float StoreRule::FOOD_COST = 1.4f;
const float StoreRule::HOUSE_COST = 0.2f;
const float StoreRule::MISC_COST = 0.7f;

StoreRule::StoreRule(Citizen& citizen) : BaseRule(citizen, STORE), foodStock(60), miscStock(60), householdStock(60), ratio(0) 
{ }

StoreRule::~StoreRule()
= default;

float StoreRule::CalculateScore()
{
    float totalScore = 0.f;
    float totalCost = 0.f;
    const auto home = dynamic_cast<HomeRule*>(citizen->FindRule(HOME));
    if (home->HasHome())
    {
        totalScore += Clamp(RESTOCK - foodStock, 0.f);
        totalCost += Clamp(RESTOCK - foodStock, 0.f) * FOOD_COST;
        totalScore += Clamp(RESTOCK - householdStock, 0.f);
        totalCost += Clamp(RESTOCK - householdStock, 0.f) * HOUSE_COST;
    }
    
    totalScore += Clamp(RESTOCK - miscStock, 0.f);
    totalCost += Clamp(RESTOCK - miscStock, 0.f) * MISC_COST;
    return citizen->Money() < totalCost ? 0 : totalScore * 10;
}

bool StoreRule::FindPlot()
{
	auto &plots = CoreController::GetSystemController()->GetSystem(STORE)->Plots();

	// Get a list of plots that fulfill out requirements ( distance < max distance
	List<Plot*> choices;
	const auto coords = citizen->Coords();
	for (auto && plot : plots)
	{
		const auto distance = plot->Coords().Distance(coords);
		if (distance < maxDistance)
		{
			choices.InsertLast(plot);
		}
	}

	// If such a list doesn't exist. This rule returns failed result false
	if (choices.Count() == 0)
	{
		return false;
	}
	const auto chosen = choices[RandomInt(0, choices.Count())];
	citizen->SetActiveRule(this);
	citizen->SetTarget(chosen);

    return true;
}

void StoreRule::EnterPlot(Plot* plot)
{
	const auto store = dynamic_cast<Store*>(plot->GetPlotType());
    if (store == nullptr) return;
    
    float restock = 0;
    float cost = 0;
    const auto home = dynamic_cast<HomeRule*>(citizen->FindRule(HOME));
    const auto money = citizen->Money();
    if (home->HasHome())
    {
        restock += MAX_STOCK - foodStock;
        cost += (MAX_STOCK - foodStock) * FOOD_COST;
        restock += MAX_STOCK - householdStock;
        cost += (MAX_STOCK - householdStock) * HOUSE_COST;
    }
    restock += MAX_STOCK - miscStock;
    cost += (MAX_STOCK - miscStock) * MISC_COST;
    
    ratio = money > cost ? 1 : money / cost;
    restock *= ratio;
    cost *= ratio;
	citizen->Wait(restock / MAX_STOCK);
	citizen->IncreaseMoney(int(cost));
    store->Payment(cost);
    store->Enter();
}

void StoreRule::LeavePlot(Plot* plot)
{
    foodStock = (MAX_STOCK - foodStock) * ratio;
    miscStock = (MAX_STOCK - miscStock) * ratio;
    householdStock = (MAX_STOCK - householdStock) * ratio;
}

void StoreRule::Update()
{
    const auto home = dynamic_cast<HomeRule*>(citizen->FindRule(HOME));
    const float deltaTime = CoreController::Instance()->GetDeltaTime();
    if (home->HasHome())
    {
        if (home->AtHome())
        {
            if (foodStock > 0)
            {
                foodStock = Clamp(foodStock - deltaTime * 0.5f, 0.f);
                const auto food = dynamic_cast<FoodRule* >(citizen->FindRule(FOOD));
                food->FillHunger(food->Hunger() + deltaTime);
            }
        }
        householdStock = Clamp(householdStock - deltaTime * 0.2f, 0.f);
    }
    
    miscStock = Clamp(miscStock - deltaTime * 0.1f, 0.f);
}