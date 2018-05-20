#include <cstdlib>
#include "Citizen.h"
#include "../../Controllers/CoreController.h"


Citizen::Citizen() 
{
    auto& plots = CoreController::Instance()->GetPlotSystem()->plots;
    coords = plots[rand() % plots.Count()]->Coords();
    moveSpeed = static_cast<float>(rand() % 5) / 900;
    target = nullptr;
    shape = CircleShape(5);
    shape.setFillColor(Color::Blue);
}


Citizen::~Citizen() = default;

/**
 * \brief Handles all update events of the citizen
 * \param deltaTime Time since last update
 */
void Citizen::Update(const float deltaTime)
{
    if (target != nullptr)
    {
        coords = coords.MoveTowards(target->Coords(), deltaTime + moveSpeed);
    }
    if (target == nullptr || coords == target->Coords())
    {
        const auto neighbours = coords.GetNeighbours();
        
        do
        {
            target = CoreController::Instance()->GetPlotSystem()->FindPlot(neighbours[rand() % 6]);
        } while (target == nullptr);
        
        delete[] neighbours;
    }
    
    auto sCoords = coords.ToScreenCoordinates();
    sCoords.X -= 2.5;
    sCoords.Y -= 2.5;
    sCoords = CoreController::Instance()->GetViewportController()->ToDrawCoord(sCoords);
    
    shape.setPosition(sCoords.X, sCoords.Y);
}

CircleShape& Citizen::GetShape()
{
    return shape;
}
