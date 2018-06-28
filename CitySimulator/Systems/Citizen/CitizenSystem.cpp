#include "CitizenSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"
#include "../../Helpers/Logger.h"
#include "../Food/FoodRule.h"
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
	Cal_Satisfactory();
}

/**
 * \brief Renders citizens;
 */
void CitizenSystem::Render() const
{
    for (auto && citizen : citizens)
    {
        
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

/**
 * \brief Handles interday rendering for citizens
 */
void CitizenSystem::RenderInterday() const
{
    for (auto && citizen : citizens)
    {
        auto & shape = citizen->GetShape();
        SFMLController::UpdateCircleSize(shape);
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
 void CitizenSystem::ResetDay()
 {
	 for (auto&& citizen : this->citizens)
	 {
		 citizen->EndDay();
	 }
 }

 void CitizenSystem::Cal_Satisfactory() const
 {
	
	 const int systemCount = CoreController::Instance()->GetSystemController()->SystemCount();
	 float* ruleScore = new float[systemCount];
	 for (int i = 0; i < systemCount; i++)
	 {
		 ruleScore[i] = 0;
	 }
	 for (auto&& citizen : citizens)
	 {
		for (int j = 0; j < systemCount; j++)
		{
			auto rulePtr = citizen->FindRule(static_cast<System>(j + 1));
            
			if (rulePtr->IsSatisfied())
			{
				ruleScore[j] += (1.f/citizenCount);
			}
		}
	 }
	 while (CoreController::Instance()->GetUIController()->GetScoreList().Count() != 0)
	 {
		 CoreController::Instance()->GetUIController()->GetScoreList().RemoveLast();
	 }
	 for (int i = 0; i < systemCount; i++)
	 {
		 CoreController::Instance()->GetUIController()->GetScoreList().InsertLast(ruleScore[i]);
	 }
	 return;

 }
