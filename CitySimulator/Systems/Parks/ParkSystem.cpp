#include "ParkSystem.hpp"
#include "Park.hpp"
#include "../Plot/PlotSystem.h"


const int ParkSystem::CLOSE_ENUF = 10;

ParkSystem::ParkSystem() : BaseSystem(PARK)
{
}


ParkSystem::~ParkSystem()
= default;

void ParkSystem::Update()
{
    // Nothing
}

int ParkSystem::Register(Plot* plot)
{
    plot->Register(new Park(plot));
    BaseSystem::Register(plot);
    return 0;
}

void ParkSystem::EndDay()
{
    List<Plot*> markForRemoval;
    for (auto && plot : plots)
    {
        if (dynamic_cast<Park*>(plot->GetPlotType())->visitors < 20)
        {
            markForRemoval.InsertLast(plot);
        }
    }

    for (auto && plot : markForRemoval)
    {
        BaseSystem::Destroy(plot);
    }
    
    List<Coordinate> newParks;
    List<int> count;
    List<Coordinate> rejected;
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto && coordinate : tooFarList)
        {
            bool found = false;
            for (int i = 0; i < newParks.Count(); ++i)
            {
                if (newParks[i].Distance(coordinate) < 10)
                {
                    ++count[i];
                    found = true;
                }
            }
            if (!found && !rejected.Contains(coordinate))
            {
                newParks.InsertLast(coordinate);
                count.InsertLast(1);
            }
        }

        for (int i = 0; i < newParks.Count(); ++i)
        {
            if (count[i] < 5)
            {
                rejected.InsertLast(newParks[i]);
                newParks.RemoveAt(i);
                count.RemoveAt(i);
                --i;
                changed = true;
            }
        }
    }
    auto&& plotSystem = CoreController::GetSystemController()->Plots();
    for (auto && newPark : newParks)
    {
        const auto plot = plotSystem->FindPlot(newPark);
        Plot* nPlot = nullptr;
        if (plot != nullptr && (plot->GetPlotType() != nullptr || plot->IsRiver()))
        {
            do
            {
                const auto neighbours = plot->Coords().GetNeighbours();
                nPlot = CoreController::GetSystemController()->Plots()->FindPlot(neighbours[rand() % 6]);
            } while (nPlot == nullptr || nPlot->IsRiver() || nPlot->GetPlotType() != nullptr );
        }
        Register(nPlot);
    }
    
    tooFarList.Clear();
}
int ParkSystem::Cost() const
{
    return -1000;
}
float ParkSystem::GetSatisfaction() const
{
    return 0.f;
}

void ParkSystem::TooFar(const Coordinate& coords)
{
    tooFarList.InsertLast(coords);
}
