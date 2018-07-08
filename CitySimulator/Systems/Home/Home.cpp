#include "Home.h"
#include "HomeRule.h"
#include "../../Helpers/Constants.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
//class HomeRule;


Home::Home(Plot* plot):Base(plot, HOME)
{
	cost = 10000;
	homeCapacity = RandomInt(50, 60);
	color = HOME_COLOR;
	score = 0;
}
void Home::Register(Citizen* citizen)
{
	//Citizen need to register it's home in this function
	//Citizen->register(*this);
	if(!Full())
		Residents.InsertLast(citizen);
}
void Home::Unregister(Citizen * citizen)
{
	if (Residents.Contains(citizen))
		Residents.Remove(citizen);
}
void Home::EndDay()
{
	//need to implement something
}
bool Home::Full()const
{
	return (homeCapacity <= NumOfFamily());
}
std::string Home::ContentString()
{
	std::stringstream ss;
	ss << "Provides home for" << std::endl <<" familes." << std::endl << std::endl;
	ss << "Maximum Capacitiy : " << homeCapacity <<  std::endl << "Family count: " << NumOfFamily();
	ss << std::endl << "(unit: house)";
	return ss.str();
}
int Home::Destroy()
{
	for (auto&& resident : Residents)
	{
		auto homeRule = dynamic_cast<HomeRule*>(resident->FindRule(HOME));
		homeRule->myHome = nullptr;
		homeRule->atHomeFlag = false;
	}
	Base::Destroy();
	return 0;
}
void Home::Enter()
{
	score += 5;
}
int Home::NumOfFamily() const
{
	int countOfFamily = 0;
	for (auto citizen : Residents)
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
				++countOfFamily;
		}
	}
	return countOfFamily;
}
Plot* Home::GetPlot() const
{
	return plot;
}
