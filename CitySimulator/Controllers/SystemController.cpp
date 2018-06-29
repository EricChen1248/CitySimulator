#include "SystemController.h"
#include "../Systems/Food/FoodSystem.h"
#include "../Systems/Bank/BankSystem.h"
#include "../Systems/Home/HomeSystem.h"
#include "../Systems/Work/WorkSystem.h"
#include "../Systems/Store/StoreSystem.h"
#include "../Systems/School/SchoolSystem.h"
#include "../Systems/Hospital/HospitalSystem.h"

SystemController::SystemController() = default;

SystemController::~SystemController()
{
    systems.Dispose();
}

/**
 * \brief Late Initialization of system controller so all pointers are in place
 */
void SystemController::Initialize()
{
    plots = new PlotSystem;
    
    
    // NONE,    FOOD,	WORK,	BANK,	HOME,	STORE, 	SCHOOL,    HOSPITAL
    BaseSystem* food = new FoodSystem();
	BaseSystem* work = new WorkSystem();
	BaseSystem* bank = new BankSystem();
	BaseSystem* home = new HomeSystem();
	BaseSystem* store = new StoreSystem();
    BaseSystem* school = new SchoolSystem();
    BaseSystem* hospital = new HospitalSystem();
    
    systems.InsertLast(food);
	systems.InsertLast(work);
	systems.InsertLast(bank);
	systems.InsertLast(home);
	systems.InsertLast(store);
    systems.InsertLast(school);
    systems.InsertLast(hospital);
    
    // TODO Remove demo
    for (auto && system : systems)
    {
        if (system->SystemType == FOOD)
        {
            for (int i = 0; i < 5; ++i)
            {
                auto plot = plots->GetRandomPlot();
                while (plot->GetPlotType() != nullptr)
                {
                    plot = plots->GetRandomPlot();
                }
                system->Register(plot);
            }
        }
		if (system->SystemType == BANK) 
		{
			for (int i = 0; i < 5; ++i) 
			{
				auto plot = plots->GetRandomPlot();
				while (plot->GetPlotType() != nullptr)
				{
					plot = plots->GetRandomPlot();
				}
				system->Register(plot);
			}
		}
		if (system->SystemType == HOME)
		{
			for (int i = 0; i < 5; ++i)
			{
				auto plot = plots->GetRandomPlot();
				while (plot->GetPlotType() != nullptr)
				{
					plot = plots->GetRandomPlot();
				}
				system->Register(plot);
			}
		}

		if (system->SystemType == WORK)
		{
			for (int i = 0; i < 30; ++i)
			{
				auto plot = plots->GetRandomPlot();
				while (plot->GetPlotType() != nullptr)
				{
					plot = plots->GetRandomPlot();
				}
				system->Register(plot);
			}
		}

		if (system->SystemType == STORE)
		{
			for (int i = 0; i < 10; ++i)
			{
				auto plot = plots->GetRandomPlot();
				while (plot->GetPlotType() != nullptr)
				{
					plot = plots->GetRandomPlot();
				}
				system->Register(plot);
			}
		}
    }
	citizens = new CitizenSystem;
}

/**
 * \brief Calls update function of each system
 */
void SystemController::Update() const
{
    citizens->Update();
    for (auto && system : systems)
    {
        system->Update();
    }
}

/**
 * \brief Calls render functions of citizens and plots
 */
void SystemController::Render() const
{
    citizens->Render();
    plots->Render();
}

/**
 * \brief Calls render function of plots
 */
void SystemController::RenderInterday() const
{
    plots->RenderInterDay();
    citizens->RenderInterday();
}

void SystemController::AdvanceDay() const
{
    plots->ClearSelections();
}



/**
 * \brief Gets the system based on system enum type
 * \param system System Type Enum of requested system
 * \return The requested system
 */
BaseSystem* SystemController::GetSystem(const System system) const
{
    for (auto && systemRef : systems)
    {
        if (systemRef->SystemType == system)
        {
            return systemRef;
        }
    }
    return nullptr;
}
void SystemController::ResetDay()
{
	citizens->ResetDay();
	for (auto&& system : systems)
	{
		system->EndDay();
	}
}

int SystemController::SystemCount() const
{
	return systems.Count();
}

void SystemController::Cal_Satisfied() const
{
	citizens->CalculateSatisfaction();
	return;
}
