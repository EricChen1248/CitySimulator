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
	mode = 1;
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
		DIRECTION dir;
		ranSeed == 0 ? (x = LEFT,y = interval ,z = adjustedRight - interval,dir = DirRIGHTDOWN) : (x = LEFT + interval, y = adjustedRight, z  = -interval, dir = DirRIGHTUP);
		Coordinate startPoint(x, y, z);
		MarkAsRiver(startPoint);
		if (ranSeed == 0)
		{
			Draw(DirRIGHTUP, DirLEFTDOWN, startPoint, points);
		}
		if (ranSeed == 1)
		{
			Draw(DirLEFTUP, DirRIGHTDOWN, startPoint, points);

		}
		
		startPoint = ranSeed == 0 ? startPoint.RightDown() : startPoint.RightUp();
		DIRECTION tempD = ranSeed == 0 ? DirRIGHTDOWN : DirRIGHTUP;
		DrawStraightLine(AXISZ, tempD, 0,points, startPoint);
		if (ranSeed == 1)
		{
			Draw(DirLEFTUP,DirRIGHTDOWN,startPoint,points);
		}
		if(ranSeed == 0)
		{
			Draw(DirRIGHTUP, DirLEFTDOWN, startPoint, points);
		}
		MarkAsRiver(startPoint);
		//Move to next 
		startPoint = startPoint.Right();
		DrawStraightLine(AXISX, DirRIGHT, interval, points, startPoint);

		ranSeed = RandomInt(0, 2);

		if (ranSeed == 0)
		{
			Draw(DirRIGHTUP, DirLEFTDOWN, startPoint, points);
			
		}
		else
		{
			Draw(DirLEFTUP, DirRIGHTDOWN, startPoint, points);	
		}
		//Mark
		MarkAsRiver(startPoint);
		//Move
		tempD = ranSeed == 0 ? DirRIGHTDOWN : DirRIGHTUP;
		AXIS tempAx = ranSeed == 0 ? AXISX : AXISY;
		int bound = ranSeed == 0 ? adjustedRight : LEFT;
		DrawStraightLine(tempAx, tempD, bound, points, startPoint);

		MarkAsRiver(startPoint);
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

void River::DrawStraightLine(const AXIS & ax, const DIRECTION & dir, const int & boundary, List<Coordinate>& inputList,Coordinate& curCoord)
{

	int tempAx = ax == AXISX ? curCoord.X() : ax == AXISY ? curCoord.Y() : curCoord.Z();
	while (tempAx != boundary)
	{
		MarkAsRiver(curCoord);
		switch (dir)
		{
		case(DirRIGHT):
		{
			inputList.InsertLast(curCoord.Up(float(1.02)*SIN60));
			inputList.InsertLast(curCoord.Down(float(1.02)*SIN60));
			curCoord = curCoord.Right();
			break;
		}
		case(DirRIGHTUP):
		{
			inputList.InsertLast(curCoord.Left(float(0.88)));
			inputList.InsertLast(curCoord.Right(float(0.88)));
			curCoord = curCoord.RightUp();
			break;
		}
		case(DirRIGHTDOWN):
		{
			inputList.InsertLast(curCoord.Right(float(0.88)));
			inputList.InsertLast(curCoord.Left(float(0.88)));
			curCoord = curCoord.RightDown();
			break;
		}
		case(DirLEFT):
		{
			inputList.InsertLast(curCoord.Down(float(1.02)*SIN60));
			inputList.InsertLast(curCoord.Up(float(1.02)*SIN60));
			curCoord = curCoord.Left();
			break;
		}
		case(DirLEFTUP):
		{
			inputList.InsertLast(curCoord.Left(float(0.88)));
			inputList.InsertLast(curCoord.Right(float(0.88)));
			curCoord = curCoord.LeftUp();
			break;
		}
		case(DirLEFTDOWN):
		{
			inputList.InsertLast(curCoord.Right(float(0.88)));
			inputList.InsertLast(curCoord.Left(float(0.88)));
			curCoord = curCoord.LeftDown();
			break;
		}

		default:
			break;
		}
		tempAx = ax == AXISX ? curCoord.X() : ax == AXISY ? curCoord.Y() : curCoord.Z();
	}
}
/*
NODIRECTION means it is not boundary
DirRight = means up
DirLEFT means down
*/
DIRECTION River::IsBoundaryOrNot(const Coordinate & coord) const
{
	if (coord.X() == RIGHT - 1)
	{
		return DirRIGHTDOWN;
	}
	if (coord.X() == LEFT)
	{
		return DirLEFTUP;
	}
	if (coord.Y() == RIGHT - 1)
	{
		return DirLEFTDOWN;
	}
	if (coord.Y() == LEFT)
	{
		return DirRIGHTUP;
	}
	if (coord.Z() == RIGHT - 1)
	{
		return DirRIGHT;
	}
	if (coord.Z() == LEFT)
	{
		return DirLEFT;
	}
	return NODIRECTION;
}
DIRECTION River::IsSixOrNot(const Coordinate & coord) const
{
	if ((coord.X() == LEFT) && (coord.Z() == (RIGHT - 1)))
	{
		return DirLEFTUP;
	}
	if ((coord.Y() == LEFT) && (coord.Z() == (RIGHT - 1)))
	{
		return DirRIGHTUP;
	}
	if ((coord.X() == (RIGHT - 1)) && (coord.Y() == LEFT))
	{
		return DirRIGHT;
	}
	if ((coord.X() == (RIGHT - 1)) && (coord.Z() == LEFT))
	{
		return DirRIGHTDOWN;
	}
	if ((coord.Y() == (RIGHT - 1)) && (coord.Z() == LEFT))
	{
		return DirLEFTDOWN;
	}
	if ((coord.X() == LEFT) && (coord.Y() == (RIGHT - 1)))
	{
		return DirLEFT;
	}
	return NODIRECTION;
}
void River::DrawCorner(DIRECTION d1, DIRECTION d2,List<Coordinate>& inputList, Coordinate& curCoord)
{
	MarkAsRiver(curCoord);
	if (d1 == DirRIGHTUP)
	{
		inputList.InsertLast(curCoord.LeftUp(float(1.02)*SIN60));
		inputList.InsertLast(curCoord.RightDown(float(1.02)*SIN60));
		curCoord = curCoord.Right();
	}
	else if(d1 == DirRIGHTDOWN)
	{
		inputList.InsertLast(curCoord.RightUp(float(1.02)*SIN60));
		inputList.InsertLast(curCoord.LeftDown(float(1.02)*SIN60));
		curCoord = curCoord.Right();
	}
	else
	{
		if (d2 == DirRIGHTUP)
		{
			inputList.InsertLast(curCoord.LeftUp(float(1.02)*SIN60));
			inputList.InsertLast(curCoord.RightDown(float(1.02)*SIN60));
			curCoord = curCoord.RightUp();
		}
		else if (d2 == DirRIGHTDOWN)
		{
			inputList.InsertLast(curCoord.RightUp(float(1.02)*SIN60));
			inputList.InsertLast(curCoord.LeftDown(float(1.02)*SIN60));
			curCoord = curCoord.RightDown();
		}
	}
	return;
}

void River::DrawEnd(const Coordinate& coord, List<Coordinate>& inputList)
{
	MarkAsRiver(coord);
	if (IsSixOrNot(coord) == NODIRECTION)
	{
		DIRECTION tempD = IsBoundaryOrNot(coord);
		switch (tempD)
		{
		case DirRIGHTUP:
			inputList.InsertLast(coord.LeftUp(float(0.88)));
			inputList.InsertLast(coord.RightDown(float(0.88)));
			break;
		case DirRIGHT:
			inputList.InsertLast(coord.Left(float(0.88)));
			inputList.InsertLast(coord.Right(float(0.88)));
			break;
		case DirRIGHTDOWN:
			inputList.InsertLast(coord.RightUp(float(0.88)));
			inputList.InsertLast(coord.LeftDown(float(0.88)));
			break;
		case DirLEFTDOWN:
			inputList.InsertLast(coord.RightDown(float(0.88)));
			inputList.InsertLast(coord.LeftUp(float(0.88)));
			break;
		case DirLEFT:
			inputList.InsertLast(coord.Right(float(0.88)));
			inputList.InsertLast(coord.Left(float(0.88)));
			break;
		case DirLEFTUP:
			inputList.InsertLast(coord.LeftDown(float(0.88)));
			inputList.InsertLast(coord.RightUp(float(0.88)));
			break;
		case NODIRECTION:
			break;
		default:
			break;
		}
	}
	else
	{
		DIRECTION tempD = IsSixOrNot(coord);
		switch (tempD)
		{
		case DirRIGHTUP:
			inputList.InsertLast(coord.Left(float(0.88)));
			inputList.InsertLast(coord.RightDown(float(0.88)));
			break;
		case DirRIGHT:
			inputList.InsertLast(coord.LeftUp(float(0.88)));
			inputList.InsertLast(coord.LeftDown(float(0.88)));
			break;
		case DirRIGHTDOWN:
			inputList.InsertLast(coord.RightUp(float(0.88)));
			inputList.InsertLast(coord.Left(float(0.88)));
			break;
		case DirLEFTDOWN:
			inputList.InsertLast(coord.Right(float(0.88)));
			inputList.InsertLast(coord.LeftUp(float(0.88)));
			break;
		case DirLEFT:
			inputList.InsertLast(coord.RightDown(float(0.88)));
			inputList.InsertLast(coord.RightUp(float(0.88)));
			break;
		case DirLEFTUP:
			inputList.InsertLast(coord.LeftDown(float(0.88)));
			inputList.InsertLast(coord.Right(float(0.88)));
			break;
		case NODIRECTION:
			break;
		default:
			break;
		}
	}
}

void River::Draw(const DIRECTION d1, const DIRECTION d2, const Coordinate & coord, List<Coordinate>& inputlist, float length)
{
	switch (d1)
	{
	case(DirLEFT):
		inputlist.InsertLast(coord.Left(length));
		break;
	case(DirLEFTDOWN):
		inputlist.InsertLast(coord.LeftDown(length));
		break;
	case(DirLEFTUP):
		inputlist.InsertLast(coord.LeftUp(length));
		break;
	case(DirRIGHT):
		inputlist.InsertLast(coord.Right(length));
		break;
	case(DirRIGHTDOWN):
		inputlist.InsertLast(coord.RightDown(length));
		break;
	case(DirRIGHTUP):
		inputlist.InsertLast(coord.RightUp(length));
		break;
	default:
		break;
	}
	switch (d2)
	{
	case(DirLEFT):
		inputlist.InsertLast(coord.Left(length));
		break;
	case(DirLEFTDOWN):
		inputlist.InsertLast(coord.LeftDown(length));
		break;
	case(DirLEFTUP):
		inputlist.InsertLast(coord.LeftUp(length));
		break;
	case(DirRIGHT):
		inputlist.InsertLast(coord.Right(length));
		break;
	case(DirRIGHTDOWN):
		inputlist.InsertLast(coord.RightDown(length));
		break;
	case(DirRIGHTUP):
		inputlist.InsertLast(coord.RightUp(length));
		break;
	default:
		break;
	}
	return;
}

void River::MarkAsRiver(const Coordinate & coord)
{
	auto plotPtr = CoreController::GetSystemController()->Plots()->FindPlot(coord);
	plotPtr->MarkAsRiver();
	riverPoints.InsertLast(plotPtr);
}
