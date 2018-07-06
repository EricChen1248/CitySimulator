#include "UIController.h"
#include "CoreController.h"
#include "SystemController.h"
#include "DisasterController.h"
#include "ViewPortController.h"

#include "../Helpers/HelperFunctions.h"
#include "../Systems/Plot/PlotSystem.h"


DisasterController::DisasterController() : funct(nullptr)
{
}


DisasterController::~DisasterController()
{
}

void DisasterController::Update()
{
    return;
    if (funct != nullptr)
    {
        (this->*funct)();
        return;
    }
    
    auto ui = CoreController::GetUIController();
	const int rand = RandomInt(0, 100000);
	if (rand == 1) //0.01%
	{
		//Apocalypse();
		;
	}
	else if (rand > 10 && rand <= 20) //0.1%
	{
		Earthquake();
	    ui->Flash("Earthquake!!!");
		if (rand <= 15) // 0.1% * 0.5
		{
			Tsunami();
	        ui->Flash("Tsunami!!!");
		}
	}
	else if (rand > 20 && rand <= 30) //0.1%
	{
		Tsunami();
	    ui->Flash("Tsunami!!!");
	}
	else if (rand >= 1000 && rand <= 1100) //1%
	{
		Hurricane();
	    ui->Flash("Hurricane!!!");
	}
	else if (rand >= 3000 && rand <= 3200) //2%
	{
		WildFire();
	    ui->Flash("Wild Fire!!!");
	}
	else if (rand == 2) //1%
	{
		GodsGift();
	    ui->Flash("God's Gift!!!");
	}
	else if (rand > 30 && rand <= 40) // 0.1%
	{
		AngelsAegis();
	    ui->Flash("Angel's Aegis!!!");
	}
	else if (rand > 4000 && rand <= 5000) //1%
	{
		MajestysMarvel();
	    ui->Flash("Majesty's Marvel!!!");
	}
}
/*
void DisasterController::Apocalypse()
{
	const auto& citizens = CoreController::GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i != 100)
		{
			citizen->Die();
		}
	}
	const auto& plots = CoreController::GetSystemController()->Plots()->Plots();
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
    funct = &DisasterController::earthquake;
    shakeTime = 200;
	const auto& citizens = CoreController::GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i < 5)
		{
			citizen->Die();
		}
	}
	//const auto& plots = CoreController::GetSystemController()->Plots()->Plots();
	for (int i = 0; i < 10; i++)
	{
	    auto plot = CoreController::GetSystemController()->Plots()->GetRandomPlot();
		if (plot->GetPlotType() != nullptr)
        {
            plot->Destroy();
        }
	}
}

void DisasterController::Hurricane()
{
	const auto& citizens = CoreController::GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i < 2)
		{
			citizen->Die();
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
	            auto plot = CoreController::GetSystemController()->Plots()->FindPlot(neighbor_coords[i]);
	            if (plot == nullptr) continue;
	            if (plot->GetPlotType() != nullptr)
                {
                    plot->Destroy();
                }
			}		
		}
        if (centers->GetPlotType() != nullptr)
        {
            centers->Destroy();
        }
	}
}

void DisasterController::Tsunami()
{
	const auto& citizens = CoreController::GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i < 5)
		{
			citizen->Die();
		}
	}
	//not finished!!
}

void DisasterController::WildFire()
{
	const auto& citizens = CoreController::GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		const int i = RandomInt(0, 100);
		if (i < 2)
		{
			citizen->Die();
		}
	}
	
	const auto& center = CoreController::GetSystemController()->Plots()->GetRandomPlot();
	const auto& neighbor_coords = center->Coords().GetNeighbours();
	for (int i = 0; i < 6; i++)
	{
	    auto plot = CoreController::GetSystemController()->Plots()->FindPlot(neighbor_coords[i]);
	    if (plot == nullptr) continue;
	    if (plot->GetPlotType() != nullptr)
        {
            plot->Destroy();
        }
	}
    if (center->GetPlotType() != nullptr)
    {
        center->Destroy();
    }
}

void DisasterController::MajestysMarvel()
{
	const auto& roads = CoreController::GetSystemController()->Plots()->Roads();
	for (auto && road : roads)
	{
		const int i = RandomInt(0, 4);
		if (i == 2)
		{
			road->PerformClick();
		}
	}
}

void DisasterController::AngelsAegis()
{
	const auto& roads = CoreController::GetSystemController()->Plots()->Roads();
	for (auto && road : roads)
	{
		const int i = RandomInt(0, 9);
		if (i == 5)
		{
			road->PerformClick();
		}
	}
}

void DisasterController::GodsGift()
{
	const auto& citizens = CoreController::GetSystemController()->GetCitizens();
	for (auto && citizen : citizens)
	{
		citizen->DoubleSpeed();
	}
}

void DisasterController::earthquake()
{
    if (shakeTime <= 0)
    {
        shakeTime = 0;
        funct = nullptr;
        return;
    }
    --shakeTime;
    
    auto vp = CoreController::GetViewportController();
    switch (int(shakeTime / 10) % 2)
    {
    case 0:
        vp->Left(2);
    default:
        vp->Right();
    }
}
