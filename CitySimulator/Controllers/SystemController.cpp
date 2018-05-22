#include "SystemController.h"

SystemController::SystemController() = default;

SystemController::~SystemController()
{
    systems.Dispose();
}

void SystemController::Initialize()
{
    plots = new PlotSystem;
    citizens = new CitizenSystem;
}

void SystemController::Update(const float deltaTime)
{
    citizens->Update(deltaTime);
    for (int i = 0; i < systems.Count(); ++i)
    {
        systems[i]->Update(deltaTime);
    }
}

void SystemController::Render() const
{
    citizens->Render();
    plots->Render();
}

