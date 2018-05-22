#include "CitizenSystem.h"
#include "../../Controllers/CoreController.h"


CitizenSystem::CitizenSystem()
{
    citizenCount = 5000;
#ifdef _DEBUG
    citizenCount = 1000;
#endif
    for (int i = 0; i < citizenCount; ++i)
    {
        auto plot = CoreController::Instance()->GetSystemController()->Plots();
        const auto &randomCoord = plot->GetRandomPlot()->Coords();
        auto citizen = new Citizen(randomCoord);
        citizens.InsertLast(citizen);
    }
}



CitizenSystem::~CitizenSystem()
{
    citizens.Dispose();
}

void CitizenSystem::Update(const float deltaTime)
{
    for (int i = 0; i < citizenCount; ++i)
    {
        citizens[i]->Update(deltaTime);
    }
}

void CitizenSystem::Render()
{
    for (int i = 0; i < citizenCount; ++i)
    {
        auto & shape = citizens[i]->GetShape();
        CoreController::Instance()->SfmlController()->DrawCircle(shape);
    }
}
