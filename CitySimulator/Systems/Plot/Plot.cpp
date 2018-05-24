#include "Plot.h"
#include "../../Controllers/CoreController.h"


Plot::Plot(const int x, const int y, const int z) : coords(x,y,z), size(10.f), shape(CircleShape(size)), currentType(nullptr)
{
    shape.setFillColor(Color(200,200,200));
    sCoords = coords.ToScreenCoordinates();
    sCoords.X -= size / 2;
    sCoords.Y -= size / 2;
}

CircleShape& Plot::GetShape()
{
    const auto tCoords = CoreController::Instance()->GetViewportController()->ToDrawCoord(sCoords);
    shape.setPosition(tCoords.X, tCoords.Y);
    return shape;
}

void Plot::Register(Base* base)
{  
    delete currentType;
    currentType = base;
    shape.setFillColor(base->Color());
}

void Plot::Enter(Citizen* citizen)
{
    occupants.InsertLast(citizen);
}

void Plot::Leave(Citizen* citizen)
{
    occupants.Remove(citizen);
}


Plot::~Plot() = default;
