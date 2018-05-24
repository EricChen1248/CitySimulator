#include "CitizenSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"


CitizenSystem::CitizenSystem()
{
    citizenCount = 5000;
#ifdef _DEBUG
    citizenCount = 100;
#endif
    for (int i = 0; i < citizenCount; ++i)
    {
        auto plot = CoreController::Instance()->GetSystemController()->Plots();
        const auto &randomPlot = plot->GetRandomPlot();
        auto citizen = new Citizen(randomPlot);
        citizens.InsertLast(citizen);
    }
}



CitizenSystem::~CitizenSystem()
{
    citizens.Dispose();
}

/**
 * \brief Calls update event of citizens
 */
void CitizenSystem::Update() const
{
    for (int i = 0; i < citizenCount; ++i)
    {
        citizens[i]->Update();
    }
}

/**
 * \brief Renders citizens;
 */
void CitizenSystem::Render() const
{
    for (int i = 0; i < citizenCount; ++i)
    {
        const auto citizen = citizens[i];
        auto & shape = citizen->GetShape();
        
        // If citizen is inside a plot, no need to draw them, only need to update size
        if (citizen->InPlot())
        {
            SFMLController::UpdateCircleSize(shape);
            continue;
        }
        CoreController::Instance()->SfmlController()->DrawCircle(shape);
    }
}
