#include "River.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Constants.h"

River::River() = default;

void River::Init()
{
    List<Coordinate> points;
    const auto& plots = CoreController::GetSystemController()->Plots();
    InitBoundary();
    const int adjustedRight = RIGHT - 1;
    const int rand = RandomInt((riverWidth / 2), adjustedRight - (riverWidth / 2));
    Coordinate startPoint(rand, adjustedRight - rand, LEFT);
    while (startPoint.Z() < RIGHT)
    {
        auto plotPtr = plots->FindPlot(startPoint);
        riverPoints.InsertLast(plotPtr);
        points.InsertLast(startPoint.Right(0.88));
        points.InsertLast(startPoint.Left(0.88));
        
        //0 means go left, 1 go right;
        int random = RandomInt(0, 2);
        
        if (rightBoundary.Contains(plotPtr))
        {
            random = 0;
        }
        else if (leftBoundary.Contains(plotPtr))
        {
            random = 1;
        }
        
        startPoint = random == 0 ? startPoint.LeftUp() : startPoint.RightUp();
    }
    
    shape = SFMLController::GenerateVertexArray(points);
    for (size_t i = 0; i < shape.getVertexCount(); ++i)
    {
        shape[i].color = RIVER_COLOR;
    }
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

    Coordinate leftStartPoint(0, adjustedRight, LEFT);
    Coordinate rightStartPoint(adjustedRight - riverWidth, riverWidth, LEFT);
    while (leftStartPoint.Z() < RIGHT)
    {
        auto leftPlotPtr = plots->FindPlot(leftStartPoint);
        auto rightPlotPtr = plots->FindPlot(rightStartPoint);
        leftBoundary.InsertLast(leftPlotPtr);
        rightBoundary.InsertLast(rightPlotPtr);
        
        leftStartPoint = leftStartPoint.LeftUp().RightUp();
        rightStartPoint = rightStartPoint.LeftUp().RightUp();
    }
    return;
}
