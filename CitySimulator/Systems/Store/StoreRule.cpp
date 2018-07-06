#include "StoreRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "StoreSystem.h"
#include "Store.h"
#include "../../Helpers/HelperFunctions.h"
#include "../Food/FoodRule.hpp"

const float StoreRule::MAX_STOCK = 200.f;
const float StoreRule::RESTOCK = 50.f;

StoreRule::StoreRule(Citizen& citizen) : BaseRule(citizen, STORE), foodStock(0), miscStock(0), householdStock(0)
{
    
}


StoreRule::~StoreRule()
= default;

float StoreRule::CalculateScore()
{
    const int restock = 50;
    // if (citizen->FindRule(HOME)->HasHome())
    // {
    //     return 0;
    // }
    
    float totalScore = 0.f;
    totalScore += Clamp(RESTOCK - foodStock, 0.f);
    totalScore += Clamp(RESTOCK - miscStock, 0.f);
    totalScore += Clamp(RESTOCK - householdStock, 0.f);
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
	citizen->Wait(0.1f);
	citizen->IncreaseMoney(-store->cost);
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
    //if (!citizen->FindRule(HOME)->IsHome())
    return;
    
    
    // TODO : store numbers
    float deltaTime = CoreController::Instance()->GetDeltaTime();
    if (foodStock > 0)
    {
        foodStock -= deltaTime;
        const auto food = dynamic_cast<FoodRule* >(citizen->FindRule(FOOD));
        food->FillHunger(food->Hunger() + deltaTime * 0.5f);
    }
}