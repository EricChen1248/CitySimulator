#include "CitizenSystem.h"

#include "../Plot/PlotSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"

#include "../../Helpers/Logger.h"
#include "../../Helpers/Government.h"
#include "../../Helpers/FeatureFlags.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"
CitizenSystem::CitizenSystem()
#if GENERATE_CENTROIDS
= default;
#else    
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
#endif


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
        if (citizen->IsDead()) continue;
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
            delete citizens[i];
            citizens.RemoveAt(i);
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
#if BREED
	NewCitizen();
#endif
	PeopleMarry();
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
    PruneDead();
    deathCount = 0;
}

void CitizenSystem::NewDeath()
{
    deathCount++;
}

void CitizenSystem::GenerateCentroids(const List<Plot*>& centers)
{
    for (auto && center : centers)
    {
        for (int i = 0; i < 20; ++i)
        {
            auto citizen = new Citizen(center);
            citizens.InsertLast(citizen);
        }
    }
    
    Logger::Log("INFO Created " + std::to_string(60) + " citizens");
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
		if (citizen->IsMarried()&&citizen->GetGender() == FEMALE&&citizen->Age()<= RETIREMENT_AGE)
		{
		    const float numerator = float(RandomInt(0, 101)) / 200.f;
            if (numerator < birth)
			{
				//create a new citizen and add it into Citizen system
				//The children is born by the side of their mother
				auto child = new Citizen(plot->FindPlot(citizen->Coords()), citizen, citizen->GetFamilyMember(SPOUSE));
				citizens.InsertLast(child);
			}
		}
	}
}

void CitizenSystem::PeopleMarry()
{
	for (auto&& citizen1 : citizens)
	{
		if (citizen1->Age() < WORKING_AGE)
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
			if (citizen2->Age() < WORKING_AGE)
			{
				continue;
			}
			if (citizen2->IsMarried())
			{
				continue;
			}
			const int dice = RandomInt(0, 1000);
			
			if (dice <= 500)
			{
				citizen1->Marry(citizen2);
			}
			break;
		}
	}
}

