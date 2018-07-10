#include "Home.h"
#include "HomeRule.h"
#include "../../Helpers/Constants.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"


Home::Home(Plot* plot) : Base(plot, HOME)
{
    cost = 10000;
    homeCapacity = RandomInt(20, 30);
    color = HOME_COLOR;
}

void Home::Register(Citizen* citizen)
{
    //Citizen need to register it's home in this function
    //Citizen->register(*this);
    if (!Full())
    {
        residents.InsertLast(citizen);
    }
}

void Home::Unregister(Citizen* citizen)
{
    if (residents.Contains(citizen))
    {
        residents.Remove(citizen);
    }
}

void Home::EndDay()
{
}

bool Home::Full() const
{
    return homeCapacity <= NumOfFamily();
}

int Home::numOfResidents() const
{
	return residents.Count();
}

std::string Home::ContentString()
{
    std::stringstream ss;
    ss << "Provides homes for" << std::endl << "families." << std::endl << std::endl;
    ss << "Maximum Capacity: " << homeCapacity << std::endl;
    ss << "Family count:      " << NumOfFamily();
    ss << std::endl << "(unit: household)" << std::endl;
    float avgSleepHour = 0.f;
    for (auto resident : residents)
    {
        const auto homeRule = dynamic_cast<HomeRule*>(resident->FindRule(HOME));
        avgSleepHour += homeRule->GetSleepTime() / float(residents.Count());
    }
    ss << "Avg sleeping Hour: " << std::fixed << std::setprecision(2) << avgSleepHour;
    return ss.str();
}

int Home::Destroy()
{
    for (auto&& resident : residents)
    {
        const auto homeRule = dynamic_cast<HomeRule*>(resident->FindRule(HOME));
        homeRule->myHome = nullptr;
        homeRule->atHomeFlag = false;
    }
    Base::Destroy();
    return Cost();
}

int Home::NumOfFamily() const
{
    int countOfFamily = 0;
    for (auto citizen : residents)
    {
        if (citizen->GetGender() == MALE)
        {
            if (citizen->Age() >= WORKING_AGE)
            {
                ++countOfFamily;
            }
        }
        else
        {
            if (!citizen->IsMarried() && citizen->Age() >= WORKING_AGE)
            {
                ++countOfFamily;
            }
        }
    }
    return countOfFamily;
}