#include "HospitalSystem.h"
#include "Hospital.h"
#include "HospitalRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Systems/Citizen/CitizenSystem.h"


class HospitalRule;

HospitalSystem::HospitalSystem() : BaseSystem(HOSPITAL)
{
}


HospitalSystem::~HospitalSystem() = default;

/**
 * \brief Registers a new hospital plot in the system
 * \param plot Plot to be registered
 */
int HospitalSystem::Register(Plot* plot)
{
    (*plot).Register(new Hospital(plot));
    BaseSystem::Register(plot);
	return Cost();
}


/**
 * \brief Calculates the satisfaction of the system at it's current states
 * \return Satisfaction of the hospital system
 */
float HospitalSystem::GetSatisfaction() const
{
    float score = 1.f;
    if (totalDeaths != 0)
    {
		int citizenCount = CoreController::GetSystemController()->Citizens()->CitizenCount();
		score -= float(unhappyDeath) / citizenCount;
    }

	// if hospitals are crowded
	score -= crowdedScoreMinus;
 
    return Clamp(score, 0.f, 1.f);
}


/**
 * \brief Increase tally of people that died outside of the hospital
 */
void HospitalSystem::DeathOutside() 
{
    ++unhappyDeath;
}

/**
 * \brief Increase tally of the total number of people
 */
void HospitalSystem::Death()
{
    ++totalDeaths;
}

/**
 * \brief Reset tallies
 */
void HospitalSystem::NewDay()
{
    unhappyDeath = 0;
    totalDeaths = 0;

	// Calculate hospital score(crowded part)
	crowdedHospital = 0;
	crowdedScoreMinus = 0;
	for (auto&& plot : plots)
	{
		const auto hospital = dynamic_cast<Hospital*>(plot->GetPlotType());
		if (hospital->members.Count() > hospital->comfortableCapacity)
		{
			crowdedScoreMinus += float(hospital->members.Count() - hospital->comfortableCapacity) / hospital->comfortableCapacity;
			crowdedHospital++;
		}
	}
}

/**
 * \brief Resets the day (clears log & resets plots)
 */
void HospitalSystem::EndDay()
{
    satisfactionToday = GetSatisfaction();
    for (auto && plot : plots)
    {
        plot->GetPlotType()->EndDay();
    }
}

/**
 * \brief Content string displayed in the status ui
 * \return Content string relevant to the current status of the hospital system
 */
std::string HospitalSystem::ContentString()
{
    std::stringstream ss;
    if (totalDeaths != 0 && float(unhappyDeath) / totalDeaths > 0.05f)
    {
        ss << "Too many people" << std::endl << "are dying outside" << std::endl << "of the hospital" << std::endl;
    }
    else if (crowdedHospital > 0)
	{
		ss << "There are "  << crowdedHospital << std::endl << " hospitals crowded" << std::endl;
	}
    else
    {
        ss << "The hospital system" << std::endl << "is working perfectly" << std::endl;
    }
	ss << std::endl;
    ss << "Daily Death:" << totalDeaths << std::endl;
	ss << "Death outside:" << unhappyDeath << std::endl;
    return ss.str();
    
}
