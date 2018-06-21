#include "CitizenSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"


CitizenSystem::CitizenSystem()
{
#ifdef _DEBUG
    citizenCount = 100;
#else
    citizenCount = 5000;
#endif
    
    for (int i = 0; i < citizenCount; ++i)
    {
        const auto plot = CoreController::Instance()->GetSystemController()->Plots();
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
	for (auto && citizen : citizens)
	{
		citizen->Update();
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

void CitizenSystem::RenderInterday() const
{
    for (int i = 0; i < citizenCount; ++i)
    {
        const auto citizen = citizens[i];
        auto & shape = citizen->GetShape();
        SFMLController::UpdateCircleSize(shape);
    }
}
