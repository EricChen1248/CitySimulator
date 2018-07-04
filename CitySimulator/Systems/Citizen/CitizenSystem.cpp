#include "CitizenSystem.h"

#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"
#include "../../Helpers/Logger.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"

#include "../../Helpers/FeatureFlags.h"
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
    for (auto&& citizen : citizens)
    {
        citizen->NewDay();
    }
    
#if BREED
	NewCitizen();
	PeopleMarry();
	int countMan = 0;
	int countWoman = 0;
	int marriedPeople = 0;
	int single = 0;
	//TODO: Delete the following debugging statement
	//for (auto citizen : citizens)
	//{
	//	citizen->GetGender() == Male ? countMan++ : countWoman++;
	//	citizen->IsMarried() == true ? marriedPeople++ : single++;
	//}
	//std::cout << "There are People :" << citizenCount << std::endl;
	//std::cout << "There are man :" << countMan << std::endl;
	//std::cout << "There are woman :" << countWoman << std::endl;
	//std::cout << "There are married people :" << MarriedPeople << std::endl;
	//std::cout << "There are single:" << single << std::endl;
#endif
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

/*
Brief:
After each day ends, those citizen with other half will start to have children.
*/
void CitizenSystem::NewCitizen()
{
    const float birth = Government::BirthRate() * 0.166f;
	for (auto && citizen : citizens)
	{
		if (citizen->IsMarried()&&(citizen->GetGender() == Female))
		{
		    const float numerator = float(RandomInt(0, 101)) / 100.f;

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
		if (citizen1->IsMarried())
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
			if (citizen2->IsMarried())
			{
				continue;
			}
			int dice = RandomInt(0, 1000);
			
			if (dice <= 52)
			{
				citizen1->Marry(citizen2);
				
			}
			break;
		}
	}
}

