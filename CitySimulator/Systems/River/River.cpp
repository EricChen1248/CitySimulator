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
	int adjustedRight = RIGHT - 1;
	int ram = RandomInt(0+(riverWidth/2), adjustedRight- (riverWidth / 2));
	Coordinate StartPoint(ram,adjustedRight-ram,LEFT);
	while (StartPoint.Z() < RIGHT)
	{
		auto plotPtr = plotSys->FindPlot(StartPoint);
		
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
		
		int positionX = StartPoint.X();
		int positionY = StartPoint.Y();
		ramdom == 1 ? positionX-- : positionY--;
		Coordinate tempCord(positionX, positionY, StartPoint.Z()+1);
		StartPoint = tempCord;
	}
	for (auto&& plotPtr : riverPoint)
	{
		Coordinate tempCoordR(plotPtr->Coords().X() + 1, plotPtr->Coords().Y(), plotPtr->Coords().Z() - 1);
		rightPoint.InsertLast(plotSys->FindPlot(tempCoordR));
		Coordinate tempCoordL(plotPtr->Coords().X() - 1, plotPtr->Coords().Y() + 1, plotPtr->Coords().Z());
		leftPoint.InsertLast(plotSys->FindPlot(tempCoordL));
	}
	shape = CoreController::Instance()->SfmlController()->GenerateLine(riverPoint);
	shape.setFillColor(RIVER_COLOR);
	shape.setOutlineThickness(10);
}

River::~River()
{
}

void River::Render() const
{
	CoreController::Instance()->SfmlController()->DrawLine(shape);
}

void River::Init_Boundary()
{
	int adjustedRight = RIGHT - 1;
	const int XYmove = -1;
	const int Zmove = 2;

	Coordinate leftStartPoint(0, adjustedRight, LEFT);
	Coordinate rightStartPoint(adjustedRight-riverWidth, riverWidth, LEFT);
	while (leftStartPoint.Z() < RIGHT)
	{
		auto leftPlotPtr = plotSys->FindPlot(leftStartPoint);
		auto rightPlotPtr = plotSys->FindPlot(rightStartPoint);
		leftBoundary.InsertLast(leftPlotPtr);
		rightBoundary.InsertLast(rightPlotPtr);
		Coordinate tempLeft(leftStartPoint.X() + XYmove, leftStartPoint.Y() + XYmove, leftStartPoint.Z() + Zmove);
		Coordinate tempRight(rightStartPoint.X() + XYmove, rightStartPoint.Y() + XYmove, leftStartPoint.Z() + Zmove);
		leftStartPoint = tempLeft;
		rightStartPoint = tempRight;
	}
	return;
}
