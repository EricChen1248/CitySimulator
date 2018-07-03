#include "CitizenSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"
#include "../../Helpers/Logger.h"
#include "../../Helpers/HelperFunctions.h"
#include "../Food/FoodRule.hpp"
#include "../Home/HomeRule.h"
#include "../Work/WorkRule.h"
#include"../../Helpers/Government.h"
#include <iostream>
CitizenSystem::CitizenSystem()
{
#ifdef _DEBUG
    citizenCount = 500;
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
	int countMan = 0;
	int countWoman = 0;
	int MarriedPeople = 0;
	int single = 0;
	//TODO: Delete the following debugging statement
	//for (auto citi : citizens)
	//{
	//	citi->GetGender() == Male ? countMan++ : countWoman++;
	//	citi->IsMarry() == true ? MarriedPeople++ : single++;
	//}
	//std::cout << "There are People :" << citizenCount << std::endl;
	//std::cout << "There are man :" << countMan << std::endl;
	//std::cout << "There are woman :" << countWoman << std::endl;
	//std::cout << "There are married people :" << MarriedPeople << std::endl;
	//std::cout << "There are single:" << single << std::endl;
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
/*
Brief:
After each day ends, those citizen with other half will start to have children.
*/
void CitizenSystem::NewCitizen()
{
	float birth = Government::BirthRate()*0.166f;
	for (auto && citizen : citizens)
	{
		if (citizen->IsMarry()&&(citizen->GetGender() == Female))
		{
			float numerator = float(RandomInt(0, 101)) / 100.f;

			// DEBUG

			if (numerator < birth)
			//if(true)
			{
				//create a new citizen and add it into Citizen system
				const auto plot = CoreController::GetSystemController()->Plots();
				//The children is born by the side of their mother
		
				auto citizenPtr = new Citizen(plot->FindPlot(citizen->Coords()));
				citizens.InsertLast(citizenPtr);
				//Setting
				citizenPtr->Birth(citizen,citizen->GetFamilyMember(Spouse));
			}
		}
		else
		{
			continue;
		}
	}
	citizenCount = citizens.Count();
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
		if (citizen1->Age() < 0)
		{
			continue;
		}
		if (citizen1->IsMarry())
		{
			continue;
		}
		for (auto&& citizen2 : citizens)
		{
			if (citizen1->GetGender() == citizen2->GetGender())
			{
				continue;
			}
			if (citizen2->Age() < 0)
			{
				continue;
			}
			if (citizen2->IsMarry())
			{
				continue;
			}
			int dice = RandomInt(0, 1000);
			
			if (dice <= 52)
			{
				citizen1->MarrySomeOne(citizen2);
				
			}
			break;
		}
	}
}

