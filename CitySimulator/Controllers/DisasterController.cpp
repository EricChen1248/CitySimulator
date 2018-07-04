#include "DisasterController.h"
#include "CoreController.h"
#include "../Helpers/HelperFunctions.h"



DisasterController::DisasterController()
{
}


DisasterController::~DisasterController()
{
}

void DisasterController::Update()
{
	const int rand = RandomInt(0, 10000);
	if (rand == 1) //0.01%
	{
		//Apocalypse();
		;
	}
	else if (rand > 10 && rand <= 20) //0.1%
	{
		Earthquake();
		if (rand <= 15) // 0.1% * 0.5
		{
			Tsunami();
		}
	}
	else if (rand > 20 && rand <= 30) //0.1%
	{
		Tsunami();
	}
	else if (rand >= 1000 && rand <= 1100) //1%
	{
		Hurricane();
	}
	else if (rand >= 3000 && rand <= 3200) //2%
	{
		WildFire();
	}
	else if (rand == 2) //1%
	{
		GodsGift();
	}
	else if (rand > 30 && rand <= 40) // 0.1%
	{
		AngelsAegis();
	}
	else if (rand > 4000 && rand <= 5000) //1%
	{
		MajestysMarvel();
	}
}
/*
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
	const auto& plots = CoreController::Instance()->GetSystemController()->Plots()->Plots();
	for (auto && plots : plots)
	{
		const int i = RandomInt(0, 100);
		if (i != 100)
		{
			plots->Destroy();
		}
	}
}
*/
void DisasterController::Earthquake()
{
	const auto& citizens = CoreController::Instance()->GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i < 5)
		{
			citizen->Death();
		}
	}
	//const auto& plots = CoreController::Instance()->GetSystemController()->Plots()->Plots();
	for (int i = 0; i < 10; i++)
	{
		CoreController::GetSystemController()->Plots()->GetRandomPlot()->Destroy();
	}
}

void DisasterController::Hurricane()
{
	const auto& citizens = CoreController::Instance()->GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i < 2)
		{
			citizen->Death();
		}
	}
	for (int i = 0; i < 10; i++)
	{
		const auto& centers = CoreController::GetSystemController()->Plots()->GetRandomPlot();
		const auto& neighbor_coords = centers->Coords().GetNeighbours();
		for (int j = 0; j < 6; j++)
		{
			const int k = RandomInt(0, 1);
			if (k == 0)
			{
				CoreController::GetSystemController()->Plots()->FindPlot(neighbor_coords[i])->Destroy();
			}		
		}
		centers->Destroy();
	}
}

void DisasterController::Tsunami()
{
	const auto& citizens = CoreController::Instance()->GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i < 5)
		{
			citizen->Death();
		}
	}
}

void DisasterController::WildFire()
{
	const auto& citizens = CoreController::Instance()->GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i < 2)
		{
			citizen->Death();
		}
	}
	
	const auto& center = CoreController::GetSystemController()->Plots()->GetRandomPlot();
	const auto& neighbor_coords = center->Coords().GetNeighbours();
	for (int i = 0; i < 6; i++)
	{
		CoreController::GetSystemController()->Plots()->FindPlot(neighbor_coords[i])->Destroy();
	}
	center->Destroy();
		
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