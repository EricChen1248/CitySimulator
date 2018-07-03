#include "CitizenSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"
#include "../../Helpers/Logger.h"
#include "../../Helpers/HelperFunctions.h"
#include "../Food/FoodRule.hpp"
#include "../Home/HomeRule.h"
#include "../Work/WorkRule.h"
#include"../../Helpers/Government.h"
CitizenSystem::CitizenSystem()
{
#ifdef _DEBUG
    citizenCount = 10;
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

void CitizenSystem::NewDay()
{
	NewCitizen();
	PeopleMarry();
	return;
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
                ruleScore[j] += (1.f / citizens.Count());
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

void CitizenSystem::NewCitizen()
{
	float birth = Government::BirthRate();
	for (auto && citizen : citizens)
	{
		if (citizen->IsMarry()&&(citizen->GetGender() == Male))
		{
			float numerator = float(RandomInt(0, 100)) / 100.f;
			if (numerator <= birth)
			{
				//create a new citizen and add it into Citizen system
				const auto plot = CoreController::GetSystemController()->Plots();
				//The children is born by the side of their mother
				const auto& momPlot = plot->FindPlot(citizen->GetFamilyMember(Spouse)->Coords());
				auto citizenPtr = new Citizen(momPlot);
				citizens.InsertLast(citizen);
				//Setting
				citizenPtr->Birth(citizen,citizen->GetFamilyMember(Spouse));
				citizenPtr->GetShape().setFillColor(RED);
			}
		}
		else
		{
			continue;
		}
	}
	return;
}

void CitizenSystem::PeopleMarry()
{
	//TODO: Discuss with Angel,Eric, Jianlien with the issue about circumstatnces people get marry;
	//TODO: Ask Angel to add a list in work, so I can find out Coworker faster.
	//Condition1 : Two citizen's age are close
	//Condition2 : Age above 20
	//Condition3 : Two citizen work together
	//if all condition are qualified, They would have 0.5 chances to marry each other.
	for (auto&& citizen1 : citizens)
	{
		if (citizen1->Age() <= 20)
		{
			continue;
		}
		if (citizen1->GetFamilyMember(Spouse) != nullptr)
		{
			continue;
		}
		for (auto&& citizen2 : citizens)
		{
			if (citizen2->GetGender() == citizen2->GetGender())
			{
				continue;
			}
			if (citizen2->Age() <= 20)
			{
				continue;
			}
			if (citizen2->GetFamilyMember(Spouse) != nullptr)
			{
				continue;
			}
			#ifdef _DEBUG
			int dice = 0;
			#else
			int dice = RandomInt(0, 10);
			#endif
			if (dice <= 1)
			{
				citizen1->MarrySomeOne(citizen2);
			}
		}
	}
}

