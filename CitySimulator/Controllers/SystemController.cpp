#include "SystemController.h"
#include "../Helpers/FeatureFlags.h"

#include "../Systems/Plot/Plot.h"
#include "../Systems/River/River.h"
#include "../Systems/Plot/PlotSystem.h"
#include "../Systems/Bank/BankSystem.h"
#include "../Systems/Home/HomeSystem.h"
#include "../Systems/Work/WorkSystem.h"
#include "../Systems/Food/FoodSystem.hpp"
#include "../Systems/Store/StoreSystem.h"
#include "../Systems/School/SchoolSystem.h"
#include "../Systems/Citizen/CitizenSystem.h"
#include "../Systems/Hospital/HospitalSystem.h"

SystemController::SystemController() : timeSinceUpdate(0.f), river(nullptr) { };

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
    plots->GenerateRoads();

    river = new River();
    river->Init();
    
#if GENERATE_CENTROIDS
    List<Plot*> centers;
    for (int i = 0; i < 3; ++i)
    {
        Plot* centroid = nullptr;
        while (centroid == nullptr || centroid->IsRiver())
        {
            centroid = plots->GetRandomPlot();
        }
        centers.InsertLast(centroid);
        const auto neighbours = centroid->Coords().GetNeighbours();
        Plot* target;
        for (auto&& system : systems)
        {
            int count = 0;
            switch (system->SystemType)
            {
            case FOOD:
            case WORK:
            case HOME:
                count = 1;
                break;
            default:;
            }
            for (int j = 0; j < count; ++j)
            {
                do
                {
                    target = CoreController::GetSystemController()->Plots()->FindPlot(neighbours[rand() % 6]);
                } while (target == nullptr || target->IsRiver() || target->GetPlotType() != nullptr);
                system->Register(target);
            }
        }
        delete[] neighbours;
        
    }
    
#elif not CLEAN_BUILD
    GenerateDemo();
#endif
    citizens = new CitizenSystem();
#if GENERATE_CENTROIDS
    citizens->GenerateCentroids(centers);
#endif
}

void SystemController::GenerateDemo()
{
    // TODO Remove demo
    for (auto&& system : systems)
    {
        int count = 0;
        switch (system->SystemType)
        {
        case FOOD:
            count = 10;
            break;
        case WORK:
            count = 30;
            break;
        case BANK:
        case HOME:
            count = 5;
            break;
        case STORE:
            count = 1;
            break;
        case SCHOOL: break;
        case HOSPITAL:
            count = 3;
            break;
        default:;
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
    river->Render();
    plots->RenderRoads();
    citizens->Render();
    plots->Render();
}

/**
 * \brief Calls render function of plots
 */
void SystemController::RenderInterday() const
{
    river->Render();
	plots->RenderRoads();
    plots->RenderInterDay();
}

void SystemController::AdvanceDay() const
{
	citizens->NewDay();
    for (auto && system : systems)
    {
        system->NewDay();
    }
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

const LinkedList<Citizen*>& SystemController::GetCitizens() const
{
    return citizens->Citizens();
}
