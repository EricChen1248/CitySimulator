#include "DisasterController.h"
#include "../Helpers/HelperFunctions.h"



DisasterController::DisasterController()
{
}


DisasterController::~DisasterController()
{
}

void DisasterController::Update()
{
	const int rand = RandomInt(0, 1000000);
	if (rand == 1)
	{
		Apocalypse();
	}
	else if (rand > 10 && rand <= 20)
	{
		Earthquake();
		if (rand <= 15)
		{
			Tsunami();
		}
	}
	else if (rand > 20 && rand <= 30)
	{
		Tsunami();
	}
	else if (rand >= 1000 && rand <= 2000)
	{
		Hurricane();
	}
	else if (rand >= 3000 && rand <= 3200)
	{
		WildFire();
	}

}

void DisasterController::Apocalypse()
{
	const auto& citizens = CoreController::Instance()->GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i != 100)
		{
			citizen->Death();
		}
	}
	/*const auto& plots = CoreController::Instance()->GetSystemController()->Plots()->Plots();
	for (auto && plots : plots)
	{
		const int i = RandomInt(0, 100);
		if (i != 100)
		{
			plots->Death();
			to do!
		}
	}*/
	

}

void DisasterController::Earthquake()
{
	const auto& citizens = CoreController::Instance()->GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i != 100)
		{
			citizen->Death();
		}
	}
}

void DisasterController::Hurricane()
{

}

void DisasterController::Tsunami()
{

}

void DisasterController::WildFire()
{

}

void DisasterController::MajestysMarvel()
{

}

void DisasterController::AngelsAegis()
{

}

void DisasterController::GodsGift()
{

}