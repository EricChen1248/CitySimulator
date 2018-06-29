#include "River.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Constants.h"

River::River() = default;

void River::Init()
{
    const auto& plots = CoreController::GetSystemController()->Plots();
    InitBoundary();
    const int adjustedRight = RIGHT - 1;
    const int rand = RandomInt((riverWidth / 2), adjustedRight - (riverWidth / 2));
    Coordinate startPoint(rand, adjustedRight - rand, LEFT);
    while (startPoint.Z() < RIGHT)
    {
        auto plotPtr = plots->FindPlot(startPoint);
        riverPoints.InsertLast(plotPtr);
        
        //1 means go left, 2 go right;
        int random = RandomInt(1, 2);
        
        if (rightBoundary.Contains(plotPtr))
        {
            random = 1;
        }
        else if (leftBoundary.Contains(plotPtr))
        {
            random = 2;
        }

        int positionX = startPoint.X();
        int positionY = startPoint.Y();
        random == 1 ? --positionX : --positionY;
        startPoint = Coordinate(positionX, positionY, startPoint.Z() + 1);
    }
    
    for (auto&& plot : riverPoints)
    {
        const Coordinate tempCoordR(plot->Coords().X() + 1, plot->Coords().Y(), plot->Coords().Z() - 1);
        auto ptr = plots->FindPlot(tempCoordR);
        if (ptr != nullptr)
        {
            rightPoints.InsertLast(ptr);
        }
        const Coordinate tempCoordL(plot->Coords().X() - 1, plot->Coords().Y() + 1, plot->Coords().Z());
        ptr = plots->FindPlot(tempCoordL);
        
        if (ptr != nullptr)
        {
            leftPoints.InsertLast(ptr);
        }
    }

    List<Plot*> points(62);
    for (auto && point : leftPoints)
    {
        points.InsertLast(point);
    }
    
    for (int i = rightPoints.Count() - 1; i >= 0; --i)
    {
        points.InsertLast(rightPoints[i]);
    }
    
    shape = SFMLController::GenerateConvex(points);
    shape.setFillColor(RIVER_COLOR);
    shape.setOutlineThickness(10);
}

River::~River()
= default;

void River::Render() const
{
    CoreController::SfmlController()->DrawShape(shape);
}

void River::InitBoundary()
{
    const auto& plots = CoreController::GetSystemController()->Plots();
    
    const int adjustedRight = RIGHT - 1;
    const int xyMove = -1;
    const int zMove = 2;

    Coordinate leftStartPoint(0, adjustedRight, LEFT);
    Coordinate rightStartPoint(adjustedRight - riverWidth, riverWidth, LEFT);
    while (leftStartPoint.Z() < RIGHT)
    {
        auto leftPlotPtr = plots->FindPlot(leftStartPoint);
        auto rightPlotPtr = plots->FindPlot(rightStartPoint);
        leftBoundary.InsertLast(leftPlotPtr);
        rightBoundary.InsertLast(rightPlotPtr);
        const Coordinate tempLeft(leftStartPoint.X() + xyMove, leftStartPoint.Y() + xyMove, leftStartPoint.Z() + zMove);
        const Coordinate tempRight(rightStartPoint.X() + xyMove, rightStartPoint.Y() + xyMove,
                                   leftStartPoint.Z() + zMove);
        leftStartPoint = tempLeft;
        rightStartPoint = tempRight;
    }
    return;
}
