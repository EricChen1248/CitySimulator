#include "River.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Constants.h"
River::River():plotSys(nullptr)
{}
void River::Init()
{
	plotSys = CoreController::Instance()->GetSystemController()->Plots();
	Init_Boundary();
    const int adjustedRight = RIGHT - 1;
	const int ram = RandomInt(0+(riverWidth/2), adjustedRight- (riverWidth / 2));
	Coordinate startPoint(ram,adjustedRight-ram,LEFT);
	while (startPoint.Z() < RIGHT)
	{
		auto plotPtr = plotSys->FindPlot(startPoint);
		
		riverPoint.InsertLast(plotPtr);
		//1 means go left, 2 go right;
		int ramdom = RandomInt(1, 2);
		for (auto&& forPlot : rightBoundary)
		{
			if (plotPtr == forPlot)
			{
				ramdom = 1;
				break;
			}
		}
		for (auto&& forPlot : leftBoundary)
		{
			if (plotPtr == forPlot)
			{
				ramdom = 2;
				break;
			}
		}
		
		int positionX = startPoint.X();
		int positionY = startPoint.Y();
		ramdom == 1 ? positionX-- : positionY--;
	    const Coordinate tempCord(positionX, positionY, startPoint.Z()+1);
		startPoint = tempCord;
	}
	for (auto&& plotPtr : riverPoint)
	{
		const Coordinate tempCoordR(plotPtr->Coords().X() + 1, plotPtr->Coords().Y(), plotPtr->Coords().Z() - 1);
		rightPoint.InsertLast(plotSys->FindPlot(tempCoordR));
		const Coordinate tempCoordL(plotPtr->Coords().X() - 1, plotPtr->Coords().Y() + 1, plotPtr->Coords().Z());
		leftPoint.InsertLast(plotSys->FindPlot(tempCoordL));
	}
	shape = CoreController::Instance()->SfmlController()->GenerateLine(leftPoint, rightPoint);
	shape.setFillColor(RIVER_COLOR);
	shape.setOutlineThickness(10);
}

River::~River()
= default;

void River::Render() const
{
	CoreController::Instance()->SfmlController()->DrawLine(shape);
}

void River::Init_Boundary()
{
	int adjustedRight = RIGHT - 1;
	const int xyMove = -1;
	const int zMove = 2;

	Coordinate leftStartPoint(0, adjustedRight, LEFT);
	Coordinate rightStartPoint(adjustedRight-riverWidth, riverWidth, LEFT);
	while (leftStartPoint.Z() < RIGHT)
	{
		auto leftPlotPtr = plotSys->FindPlot(leftStartPoint);
		auto rightPlotPtr = plotSys->FindPlot(rightStartPoint);
		leftBoundary.InsertLast(leftPlotPtr);
		rightBoundary.InsertLast(rightPlotPtr);
		const Coordinate tempLeft(leftStartPoint.X() + xyMove, leftStartPoint.Y() + xyMove, leftStartPoint.Z() + zMove);
		const Coordinate tempRight(rightStartPoint.X() + xyMove, rightStartPoint.Y() + xyMove, leftStartPoint.Z() + zMove);
		leftStartPoint = tempLeft;
		rightStartPoint = tempRight;
	}
	return;
}
