#include "StoreRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "StoreSystem.h"
#include "Store.h"




StoreRule::StoreRule(Citizen& citizen) : BaseRule(citizen, STORE), materialNeed(0)
{
    
}


StoreRule::~StoreRule()
= default;

float StoreRule::CalculateScore()
{
    return 0;
}

bool StoreRule::FindPlot()
{
	auto &plots = CoreController::Instance()->GetSystemController()->GetSystem(FOOD)->Plots();

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
	const auto chosen = choices[CoreController::RandomInt(0, choices.Count())];
	citizen->SetActiveRule(this);
	citizen->SetTarget(chosen);

    return true;
}

void StoreRule::EnterPlot(Plot* plot)
{
	const auto store = dynamic_cast<Store*>(plot->GetPlotType());
	citizen->Wait(8.f);
	citizen->IncreaseMoney(-store->cost);
	store->Enter();
}

void StoreRule::LeavePlot(Plot* plot)
{
	materialNeed = 0;
}

void StoreRule::Update()
{
	int i = CoreController::RandomInt(1, 100);
	
	if (i <= 80)
		materialNeed += 1 * CoreController::Instance()->GetDeltaTime() / 100 ;
	else if (i <= 99)
		materialNeed += 10 * CoreController::Instance()->GetDeltaTime() / 100;
	else if (i == 100)
		materialNeed += 50 * CoreController::Instance()->GetDeltaTime() / 100;
}

bool StoreRule::IsSatisfied()
{
    return materialNeed <= 20;
}
