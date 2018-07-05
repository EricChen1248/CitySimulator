#include "CitizenSystem.h"

#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"
#include "../../Helpers/Logger.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"

#include "../../Helpers/FeatureFlags.h"
CitizenSystem::CitizenSystem()
{
#ifdef _DEBUG
    const int citizenCount = 500;
#else
    const int citizenCount = 5000;
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
 * \brief Triggers new day events for citizens and handles marriage and birth
 */
void CitizenSystem::NewDay()
{

	for (auto&& citizen : citizens)
	{
		citizen->NewDay();
	}
	PeopleMarry();
#if BREED
	NewCitizen();
#endif
	
	return;
}
/**
* \brief: Triggers end day of each citizen
*/
void CitizenSystem::EndDay()
{
    for (auto&& citizen : citizens)
    {
        citizen->EndDay();
    }
}

/**
 * \brief Handles birth of citizens, based on married people and birthrate
 */
void CitizenSystem::NewCitizen()
{
    const float birth = Government::BirthRate() * 0.166f;
	const auto plot = CoreController::GetSystemController()->Plots();
	for (auto && citizen : citizens)
	{
		if (citizen->IsMarried()&&(citizen->GetGender() == FEMALE))
		{
		    const float numerator = float(RandomInt(0, 101)) / 100.f;

			// DEBUG

			if (numerator < birth)
			{
				//create a new citizen and add it into Citizen system
				//The children is born by the side of their mother
				auto child = new Citizen(plot->FindPlot(citizen->Coords()), citizen, citizen->GetFamilyMember(SPOUSE));
				citizens.InsertLast(child);
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
			const int dice = RandomInt(0, 1000);
			
			if (dice <= 52)
			{
				citizen1->Marry(citizen2);
			}
			break;
		}
	}
}

