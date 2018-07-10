#include "HomeSystem.h"
#include "HomeRule.h"
#include "Home.h"

#include "../../Helpers/HelperFunctions.h"
#include "../../Controllers/CoreController.h"

HomeSystem::HomeSystem(): BaseSystem(HOME) {}

int HomeSystem::Register(Plot* plot)
{
    // plot need to register a base first;
    // base(home) will assign a random capacity 
    plot->Register(new Home(plot));
    // Because BaseSystem is not a abstract function, and we didn't and have to overload FUNCTION REGISTER
    BaseSystem::Register(plot);
    return Cost();
}

HomeSystem::~HomeSystem()
= default;

void HomeSystem::Update() {}

/*
TODO:Adding more grading system
should be adjusted to whether they have convinent live,
how long does it take them to work : friend Workrule;
>> how far is their job from their work, and how many building are arround.
*/

float HomeSystem::GetSatisfaction() const
{
    auto&& citizenList = CoreController::GetSystemController()->GetCitizens();
    float count = 0.f;
    float avgSleepHour = 0.f;
    //how many people have house;
    const float denom = 1.f / citizenList.Count();
    for (auto&& citizen : citizenList)
    {
        //count how many people have house
        const auto home = dynamic_cast<HomeRule*>(citizen->FindRule(HOME));
        // TODO : error?
        count += home->HasHome() ? denom : 0;
        avgSleepHour += home->GetSleepTime() / 8.f * denom;
    }
    count = 0.5f * count + 0.5f * avgSleepHour;

    return Clamp(count, 0.f, 1.f);
}

void HomeSystem::EndDay()
{
    for (auto&& plot : plots)
    {
        plot->GetPlotType()->EndDay();
    }
}

void HomeSystem::NewDay()
{
    CalculateTotalFamily();
	for (auto&& plot : plots)
	{
		auto && home = dynamic_cast<Home*>(plot->GetPlotType());
	}
}

void HomeSystem::CalculateTotalFamily()
{
    familyCount = 0;
    auto&& citizenList = CoreController::GetSystemController()->GetCitizens();
    for (auto&& citizen : citizenList)
    {
        if (citizen->Age() >= WORKING_AGE)
        {
            if (citizen->GetGender() == MALE)
            {
                familyCount++;
            }
            else
            {
                if (!citizen->IsMarried())
                {
                    familyCount++;
                }
            }
        }
    }
}

std::string HomeSystem::ContentString()
{
    std::stringstream ss;
    //ss << "Provide your citizen" << std::endl;
    //ss << "a warm house. People" << std::endl;
    //ss << "get unsatisfied if" << std::endl;
    //ss << "1.don't have home." << std::endl;
    //ss << "2.Home is too far, thus" << std::endl;
    //ss << "  don't sleep much.";
    auto&& citizenList = CoreController::GetSystemController()->GetCitizens();
    const float denom = 1.f / citizenList.Count();
    float count = 0.f;
    float avgSleepHour = 0.f;
    //how many people have house;
    for (auto&& citizen : citizenList)
    {
        const auto&& home = dynamic_cast<HomeRule*>(citizen->FindRule(HOME));
        //count how many people have house
        count += home->HasHome() ? denom : 0;
        avgSleepHour += home->GetSleepTime() * denom;
    }
    if (count < 0.8f)
    {
        ss << "Build more home to" << std::endl << "handle homeless people." << std::endl;
    }
    if (avgSleepHour < 6.f)
    {
        ss << "People go home late," << std::endl << "perhaps relocate some" << std::endl << "home?" << std::endl;
    }
    if (count > 0.8f && avgSleepHour > 6.f)
    {
        ss << "Citizen are very" << std::endl << "satisfied." << std::endl;
    }
    ss << std::endl;
    ss << "Homeless people: " << int((1.f - count) * float(citizenList.Count())) << std::endl;
    ss << "Avg Sleeping hour: " << std::fixed << std::setprecision(2) << avgSleepHour;
    return ss.str();
}
