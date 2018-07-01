#include "River.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Constants.h"

River::River() = default;

void River::Init()
{
    List<Coordinate> points;
    const auto& plots = CoreController::GetSystemController()->Plots();
    const int adjustedRight = RIGHT - 1;
    const int rand = RandomInt((riverWidth / 2), adjustedRight - (riverWidth / 2));


	//Mode 0 : straight river cuting city into half; Mode 1: cutting it vertically 
	int mode = RandomInt(0,2);

	switch (mode)
	{
	case(0):
	{
		InitBoundary();
		Coordinate startPoint(rand, adjustedRight - rand, LEFT);
		while (startPoint.Z() < RIGHT)
		{
			auto plotPtr = plots->FindPlot(startPoint);
			riverPoints.InsertLast(plotPtr);
			plotPtr->MarkAsRiver();
			points.InsertLast(startPoint.Right(float(0.88)));
			points.InsertLast(startPoint.Left(float(0.88)));
			
			

			// 0 means go left, 1 go right;
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
		break;
	}
	case(1):
	{
		
		//0 means start from LeftUp going rightDown; 1 means start from LeftDown going  right up 
		int ranSeed = RandomInt(0, 2);
		int interval = adjustedRight / 2;
		int x, y, z;
		ranSeed == 0 ? (x = LEFT,y = interval ,z = adjustedRight - interval) : (x = LEFT + interval, y = adjustedRight, z  = -interval);
		Coordinate startPoint(x, y, z);
		auto plotPtr = plots->FindPlot(startPoint);
		riverPoints.InsertLast(plotPtr);
		plotPtr->MarkAsRiver();
		if (ranSeed == 0)
		{
			points.InsertLast(startPoint.RightUp(float(0.88)));
			points.InsertLast(startPoint.LeftDown(float(0.88)));
		}
		if (ranSeed == 1)
		{
			points.InsertLast(startPoint.LeftUp(float(0.88)));
			points.InsertLast(startPoint.RightDown(float(0.88)));
		}
		startPoint = ranSeed == 0 ? startPoint.RightDown() : startPoint.RightUp();
		while (startPoint.Z() != 0)
		{
			auto plotPtr = plots->FindPlot(startPoint);
			riverPoints.InsertLast(plotPtr);
			plotPtr->MarkAsRiver();
			if (ranSeed == 0)
			{
				points.InsertLast(startPoint.Right(float(0.88)));
				points.InsertLast(startPoint.Left(float(0.88)));
			}
			else
			{
				points.InsertLast(startPoint.Left(float(0.88)));
				points.InsertLast(startPoint.Right(float(0.88)));
			}
			startPoint = (ranSeed == 0) ? startPoint.RightDown(): startPoint.RightUp();
		}

		if (ranSeed == 1)
		{
			points.InsertLast(startPoint.LeftUp(float(0.88)));
			points.InsertLast(startPoint.RightDown(float(0.88)));
		}
		if(ranSeed == 0)
		{
			points.InsertLast(startPoint.RightUp(float(0.88)));
			points.InsertLast(startPoint.LeftDown(float(0.88)));
			
		}
		startPoint = startPoint.Right();
		while (startPoint.X() < interval)
		{
			auto plotPtr = plots->FindPlot(startPoint);
			riverPoints.InsertLast(plotPtr);
			plotPtr->MarkAsRiver();
			if (ranSeed == 1)
			{
				points.InsertLast(startPoint.Up(float(1.02)*SIN60));
				points.InsertLast(startPoint.Down(float(1.02)*SIN60));
				
			}
			if(ranSeed == 0)
			{
				points.InsertLast(startPoint.Up(float(1.02)*SIN60));
				points.InsertLast(startPoint.Down(float(1.02)*SIN60));
				
			}
			startPoint = startPoint.Right();
		}

		//ranSeed 0 : means going rightDown; 1 means: going rightUp

		ranSeed = RandomInt(0, 2);
		
		if (ranSeed == 0)
		{
			points.InsertLast(startPoint.RightUp(float(0.88)));
			points.InsertLast(startPoint.LeftDown(float(0.88)));
			
		}
		else
		{
			points.InsertLast(startPoint.LeftUp(float(0.88)));
			points.InsertLast(startPoint.RightDown(float(0.88)));
			
		}
		startPoint = ranSeed == 0 ? startPoint.RightDown() : startPoint.RightUp();
		bool boundary = true;
		while (boundary)
		{
			auto plotPtr = plots->FindPlot(startPoint);
			riverPoints.InsertLast(plotPtr);
			plotPtr->MarkAsRiver();
			if (ranSeed == 0)
			{
				points.InsertLast(startPoint.Right(float(0.88)));
				points.InsertLast(startPoint.Left(float(0.88)));
				
			}
			else
			{
				points.InsertLast(startPoint.Left(float(0.88)));
				points.InsertLast(startPoint.Right(float(0.88)));
			}
			startPoint = ranSeed == 0 ? startPoint.RightDown() : startPoint.RightUp();
			ranSeed == 0 ? (startPoint.X() == adjustedRight ? boundary = false : boundary = true) : (startPoint.Y() == (LEFT) ? boundary = false: boundary = true);
		}
		auto plotPtr1 = plots->FindPlot(startPoint);
		riverPoints.InsertLast(plotPtr1);
		plotPtr1->MarkAsRiver();
		if (ranSeed == 0)
		{
			points.InsertLast(startPoint.RightUp(float(0.88)));
			points.InsertLast(startPoint.LeftDown(float(0.88)));

		}
		if (ranSeed == 1)
		{
			points.InsertLast(startPoint.LeftUp(float(0.88)));
			points.InsertLast(startPoint.RightDown(float(0.88)));
		}
		shape = SFMLController::GenerateVertexArray(points);
		for (size_t i = 0; i < shape.getVertexCount(); ++i)
		{
			shape[i].color = RIVER_COLOR;
		}
		break;
	}
	default:
		break;
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
	Coordinate rightStartPoint((adjustedRight - riverWidth), (riverWidth), LEFT);
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
