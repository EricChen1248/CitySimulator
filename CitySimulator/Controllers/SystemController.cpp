#include "SystemController.h"
#include "../Systems/Bank/BankSystem.h"
#include "../Systems/Home/HomeSystem.h"
#include "../Systems/Work/WorkSystem.h"
#include "../Systems/Food/FoodSystem.hpp"
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

    river.Init();

    // TODO Remove demo
    for (auto&& system : systems)
    {
        int count = 0;
        switch (system->SystemType)
        {
        case FOOD:
            count = 3;
            break;
        case WORK:
            count = 30;
            break;
        case BANK:
        case HOME:
            count = 5;
            break;
        case STORE:
            count = 10;
            break;
        case SCHOOL: break;
        case HOSPITAL: break;
        default: ;
        }

        for (int i = 0; i < count; ++i)
        {
            auto plot = plots->GetRandomPlot();
            while (plot->GetPlotType() != nullptr || plot->IsRiver())
            {
                plot = plots->GetRandomPlot();
            }
            system->Register(plot);
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
    for (auto&& system : systems)
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
    river.Render();
}

/**
 * \brief Calls render function of plots
 */
void SystemController::RenderInterday() const
{
    plots->RenderInterDay();
    river.Render();
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
    switch (system)
    {
    case FOOD:
    case WORK:
    case BANK:
    case HOME:
    case STORE:
    case SCHOOL:
    case HOSPITAL:
        return systems[system - 1];
    default:
        return nullptr;
    }
}

void SystemController::ResetDay()
{
    citizens->EndDay();
    for (auto&& system : systems)
    {
        system->EndDay();
    }
}

int SystemController::SystemCount() const
{
    return systems.Count();
}

void SystemController::CalSatisfied() const
{
    citizens->CalculateSatisfaction();
    return;
}
