#include "SystemController.h"
#include "../Systems/Food/FoodSystem.h"

SystemController::SystemController() = default;

SystemController::~SystemController()
{
    systems.Dispose();
    
}

void SystemController::Initialize()
{
    plots = new PlotSystem;
    citizens = new CitizenSystem;
    
    BaseSystem* food = new FoodSystem();
    systems.InsertLast(food);
    // TODO Remove food demo
    for (int j = 0; j < systems.Count(); ++j)
    {
        const auto system = systems[j];
        if (system->SystemType == FOOD)
        {
            for (int i = 0; i < 5; ++i)
            {
                auto plot = plots->GetRandomPlot();
                while (plot->GetPlotType() != nullptr)
                {
                    plot = plots->GetRandomPlot();
                }
                system->Register(plot);
            }
        }
    }
}

void SystemController::Update() const
{
    citizens->Update();
    for (int i = 0; i < systems.Count(); ++i)
    {
        systems[i]->Update();
    }
}

void SystemController::Render() const
{
    citizens->Render();
    plots->Render();
}

BaseSystem* SystemController::GetSystem(const System system) const
{
    for (int i = 0; i < systems.Count(); ++i)
    {
        if (systems[i]->SystemType == system)
        {
            return systems[i];
        }
    }
    return nullptr;
}

