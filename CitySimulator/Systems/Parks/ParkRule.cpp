#include "ParkRule.hpp"
#include "Park.hpp"
#include "ParkSystem.hpp"
#include "../Plot/Plot.h"
#include "../Base/BaseSystem.h"
#include "../../Helpers/HelperFunctions.h"
#include "../Plot/PlotSystem.h"


ParkRule::ParkRule(Citizen& citizen) : BaseRule(citizen, PARK)
{
}


ParkRule::~ParkRule()
= default;

float ParkRule::CalculateScore()
{
    return 3.f;
}

bool ParkRule::FindPlot()
{
    citizen->SetActiveRule(this);
    if (currentPark != nullptr && citizen->Coords() == parkSide)
    {
        Plot* target;
        const auto neighbours = parkSide.GetNeighbours();
        do
        {
            target = CoreController::GetSystemController()->Plots()->FindPlot(neighbours[rand() % 6]);
        } while (target == nullptr || target->IsRiver());
        
        citizen->SetTarget(target);
        parkSide = target->Coords();
        return true;
    }
    const auto parks = dynamic_cast<ParkSystem*>(CoreController::GetSystemController()->GetSystem(PARK));
    auto& plots = parks->Plots();
    int distance = INT_MAX;
    Plot* closest = nullptr;
    for (auto && plot : plots)
    {
        if (!Pathable(plot->Coords(), citizen->Coords())) continue;
        const int dist = plot->Coords().Distance(citizen->Coords());
        if (dist < distance && dist < 10) 
        {
            closest = plot;
            distance = dist;
        }
    }

    if (distance > ParkSystem::CLOSE_ENUF)
    {
        parks->TooFar(citizen->Coords());
    }

    if (closest == nullptr)
    {
        return false;
    }
    
    Plot* target;
    const auto neighbours = closest->Coords().GetNeighbours();
    do
    {
        target = CoreController::GetSystemController()->Plots()->FindPlot(neighbours[rand() % 6]);
    } while (target == nullptr || target->IsRiver());
    
    currentPark = closest;
    citizen->SetTarget(target);
    parkSide = target->Coords();
    return true;
}
void ParkRule::EnterPlot(Plot* plot)
{
    if (currentPark->GetPlotType() == nullptr)
    {
        return;
    }
    currentPark->GetPlotType()->Enter();
    citizen->Wait(float(RandomInt(0,100)) / 100);
}

void ParkRule::LeavePlot(Plot* plot)
{
    // nothing
}
void ParkRule::Update()
{
    // nothing
}
