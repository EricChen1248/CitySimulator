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
    for (int i = 0; i < citizenCount; ++i)
    {
        const auto plot = CoreController::GetSystemController()->Plots();
        const auto& randomPlot = plot->GetRandomPlot();
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
    CalculateSatisfaction();
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

void CitizenSystem::CalculateSatisfaction() const
{
    const int systemCount = CoreController::GetSystemController()->SystemCount();
    float* ruleScore = new float[systemCount];
    for (int i = 0; i < systemCount; i++)
    {
        ruleScore[i] = 0;
    }
    for (auto&& citizen : citizens)
    {
        for (int j = 0; j < systemCount; j++)
        {
            auto rulePtr = citizen->FindRule(System(j + 1));

            if (rulePtr->IsSatisfied())
            {
                ruleScore[j] += (1.f / citizenCount);
            }
        }
    }
    
    ruleScore[FOOD-1] = CoreController::GetSystemController()->GetSystem(FOOD)->GetSatisfaction();
    while (CoreController::GetUIController()->GetScoreList().Count() != 0)
    {
        CoreController::GetUIController()->GetScoreList().RemoveLast();
    }
    for (int i = 0; i < systemCount; i++)
    {
        CoreController::GetUIController()->GetScoreList().InsertLast(ruleScore[i]);
    }
    delete [] ruleScore;

    return;
}
