#include <cstdlib>
#include "Citizen.h"
#include "../../Controllers/CoreController.h"


Citizen::Citizen() : coords(0, 0, 0)
{
    coords = CoreController::Instance()->GetPlotSystem()->plots[rand() % 30]->Coords();
    moveSpeed = static_cast<float>(rand() % 5) / 900;
    target = nullptr;
}


Citizen::~Citizen() = default;

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
}

sf::CircleShape Citizen::GetShape() const
{
    CircleShape circle(5);
    circle.setFillColor(Color::Blue);
    auto sCoords = coords.ToScreenCoordinates();
    sCoords.X -= 2.5;
    sCoords.Y -= 2.5;
    sCoords = CoreController::Instance()->GetMapController()->ToDrawCoord(sCoords);
    circle.setPosition(sCoords.X, sCoords.Y);
    return circle;
}
