#include "SystemController.h"
#include "../Systems/Food/FoodSystem.h"

SystemController::SystemController() = default;

SystemController::~SystemController()
{
    systems.Dispose();
    
}

/**
 * \brief Late Initialization of system controller so all pointers are in place
 */
void SystemController::Initialize()
{
    plots = new PlotSystem;
    citizens = new CitizenSystem;
    
    BaseSystem* food = new FoodSystem();
    systems.InsertLast(food);
    // TODO Remove food demo
    for (auto && system : systems)
    {
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

/**
 * \brief Calls update function of each system
 */
void SystemController::Update() const
{
    citizens->Update();
    for (auto && system : systems)
    {
        system->Update();
    }
}

/**
 * \brief Calls render functions of citizens and plots
 */
void SystemController::Render() const
{
    citizens->Render();
    plots->Render();
}

/**
 * \brief Gets the system based on system enum type
 * \param system System Type Enum of requested system
 * \return The requested system
 */
BaseSystem* SystemController::GetSystem(const System system) const
{
    for (auto && systemRef : systems)
    {
        if (systemRef->SystemType == system)
        {
            return systemRef;
        }
    }
    return nullptr;
}

