#include "CitizenSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"
#include "../../Helpers/Logger.h"
#include "../Food/FoodRule.hpp"
#include "../Home/HomeRule.h"

CitizenSystem::CitizenSystem()
{
#ifdef _DEBUG
    citizenCount = 100;
#else
    citizenCount = 5000;
#endif

    Logger::Log("Created " + std::to_string(citizenCount) + " citizens");
    
    const auto plots = CoreController::GetSystemController()->Plots();
    
    for (int i = 0; i < citizenCount; ++i)
    {
        Plot* randomPlot = plots->GetRandomPlot();
        while (randomPlot->IsRiver())
        {
            randomPlot = plots->GetRandomPlot();
        }
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
    for (auto&& citizen : citizens)
    {
        citizen->Update();
    }
}

/**
 * \brief Renders citizens;
 */
void CitizenSystem::Render() const
{
    for (auto&& citizen : citizens)
    {
        CoreController::SfmlController()->DrawShape(citizen->GetShape());
    }
}

/**
 * \brief Prunes all dead people at the end of the day
 */
void CitizenSystem::PruneDead()
{
    for (int i = 0; i < citizens.Count(); ++i)
    {
        if (citizens[i]->IsDead())
        {
            citizens.Remove(i);
            --i;
        }
    }
}

/**
* \brief: assign every person a home
*/
void CitizenSystem::EndDay()
{
    for (auto&& citizen : citizens)
    {
        citizen->EndDay();
    }
}
