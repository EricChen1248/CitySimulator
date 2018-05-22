#include <cstdlib>
#include "Citizen.h"
#include "../../Controllers/CoreController.h"


Citizen::Citizen(const Coordinate& coords) : Money(0), coords(coords), target(nullptr)
{
    moveSpeed = 1 + static_cast<float>(CoreController::RandomInt(0, 40) - 20) / 100;
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
        coords = coords.MoveTowards(target->Coords(), deltaTime * moveSpeed);
    }
    if (target == nullptr || coords == target->Coords())
    {
        const auto neighbours = coords.GetNeighbours();
        
        do
        {
            target = CoreController::Instance()->GetSystemController()->Plots()->FindPlot(neighbours[rand() % 6]);
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

void Citizen::FindNextTarget()
{
    float bestScore = 0;
    BaseRule* rule = nullptr;
    for (int i = 0; i < rules.Count(); ++i)
    {
        const auto score = rules[i]->CalculateScore();
        if (rule == nullptr || score > bestScore)
        {
            bestScore = score;
            rule = rules[i];
        }
        
    }
}
