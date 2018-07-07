#include "HospitalSystem.h"
#include "Hospital.h"
#include "HospitalRule.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"


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
    return 0;
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
         score -= float(unhappyDeath) / totalDeaths;
    }
    
    // TODO : ANGEL add if your hospitals are crowded
    
    return Clamp(score, 0.f, 1.f);
}

/**
 * \brief MISSING
 */
void HospitalSystem::Update()
{
    for (auto && plot : plots)
    {
        // Do this if you want to get the plot type (class hospital)
        //const auto rule = dynamic_cast<Hospital*> (plot->GetPlotType());
        
        // Tallying and adding score for occupant count. Positive for within limit people, negative for over
        const auto count = plot->GetOccupantCount();
        score += (std::min(count, maxOccupantCount) * scorePerOccupant - std::max(count - maxOccupantCount, 0) * overPenalty) * CoreController::Instance()->GetDeltaTime();
    }
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
    totalDeaths = 0;
}

/**
 * \brief Reset tallies
 */
void HospitalSystem::NewDay()
{
    unhappyDeath = 0;
    totalDeaths = 0;
}

/**
 * \brief Resets the day (clears log & resets plots)
 */
void HospitalSystem::EndDay()
{
    for (auto && plot : plots)
    {
        plot->GetPlotType()->EndDay();
    }
    unsatisfiedLog.Dispose();
    satisfiedLog.Dispose();
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
        {
            ss << "Too many people" << std::endl << "are dying outside" << std::endl << "of the hospital";
        }
    }
    // TODO : add your response string if your hospitals are too crowded
    else
    {
        ss << "The hospital system" << std::endl << "is working perfectly" << std::endl;
    }
    
    
    ss << "Daily Death:" << totalDeaths;
    return ss.str();
    
}
