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
* \brief: assign every people a home
*/
 void CitizenSystem::ResetDay()
 {
	 for (auto&& citizen : this->citizens)
	 {
		 citizen->EndDay();
	 }
 }

 void CitizenSystem::Cal_Satisfactory(List<float>& scoreList) const
 {
	 //TODO: add all of system;Maybe can use indexing to make this perform better????
	 
	 float food = 0;
	 float home = 0;
	 
	 for (auto&& citizen : citizens)
	 {
		 auto foodRule = dynamic_cast<FoodRule*>(citizen->FindRule(FOOD));
		 auto homeRule = dynamic_cast<HomeRule*>(citizen->FindRule(HOME));
		 if (homeRule->IsSatisfied())
		 {
			 ++home;
		 }
		 if (foodRule->IsSatisfied())
		 {
			 ++food;
		 }

	 }

	 food = (food / static_cast<float>(citizenCount));
	 home = (home / static_cast<float>(citizenCount));
	 while (scoreList.Count() != 0)
	 {
		 scoreList.RemoveLast();
	 }
	 scoreList.InsertLast(home);
	 scoreList.InsertLast(food);
	 return;
 }
