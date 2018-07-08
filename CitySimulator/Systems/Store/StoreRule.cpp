#include "StoreRule.h"
#include "Store.h"
#include "StoreSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../Food/FoodRule.hpp"
#include "../Home/HomeRule.h"

const float StoreRule::MAX_STOCK = 200.f;
const float StoreRule::RESTOCK = 50.f;

const float StoreRule::FOOD_COST = 0.5f;
const float StoreRule::HOUSE_COST = 1.f;
const float StoreRule::MISC_COST = 2.f;

StoreRule::StoreRule(Citizen& citizen) : BaseRule(citizen, STORE), foodStock(60), miscStock(60), householdStock(60)
{
    
}


StoreRule::~StoreRule()
= default;

float StoreRule::CalculateScore()
{
    float totalScore = 0.f;
    const auto home = dynamic_cast<HomeRule*>(citizen->FindRule(HOME));
    if (home->HasHome())
    {
        totalScore += Clamp(RESTOCK - foodStock, 0.f);
        totalScore += Clamp(RESTOCK - householdStock, 0.f);
    }
    
    totalScore += Clamp(RESTOCK - miscStock, 0.f);
    // TODO : adjust store rule score multiplier
    return totalScore * 5;
    
}

bool StoreRule::FindPlot()
{
	auto &plots = CoreController::GetSystemController()->GetSystem(STORE)->Plots();

	// Get a list of plots that fulfill out requirements ( distance < max distance
	List<Plot*> choices;
	for (auto && plot : plots)
	{
		auto coords = citizen->Coords();
		const auto distance = plot->Coords().Distance(coords);
		if (distance < maxDistance)
		{
			auto p = plot;
			choices.InsertLast(p);
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
    if (home->HasHome())
    {
        restock += MAX_STOCK - foodStock;
        cost += (MAX_STOCK - foodStock) * FOOD_COST;
        restock += MAX_STOCK - householdStock;
        cost += (MAX_STOCK - householdStock) * HOUSE_COST;
    }
    restock += MAX_STOCK - miscStock;
    cost += (MAX_STOCK - miscStock) * MISC_COST;
    
	citizen->Wait(restock / MAX_STOCK);
	citizen->IncreaseMoney(cost);
    store->Payment(cost);
    store->Enter();
}

void StoreRule::LeavePlot(Plot* plot)
{
    foodStock = MAX_STOCK;
    miscStock = MAX_STOCK;
    householdStock = MAX_STOCK;
}

void StoreRule::Update()
{
    // TODO : store update checks
    const auto home = dynamic_cast<HomeRule*>(citizen->FindRule(HOME));
    const float deltaTime = CoreController::Instance()->GetDeltaTime();
    if (home->HasHome())
    {
        if (home->AtHome())
        {
            // TODO : store numbers
            if (foodStock > 0)
            {
                foodStock = Clamp(foodStock - deltaTime, 0.f);
                const auto food = dynamic_cast<FoodRule* >(citizen->FindRule(FOOD));
                food->FillHunger(food->Hunger() + deltaTime * 0.5f);
            }
        }
        householdStock = Clamp(householdStock - deltaTime * 0.5f, 0.f);
    }
    
    miscStock = Clamp(miscStock - deltaTime * 1.5f, 0.f);
}