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
	RIVERMODE mode = static_cast<RIVERMODE> (RandomInt(0,3));
	//mode = ModeCIRCLE;

	switch (mode)
	{
	case(ModeSTRAIGHT):
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
	case(ModeACCROSS):
	{
		//0 means start from LeftUp going rightDown; 1 means start from LeftDown going  right up 
		int ranSeed = RandomInt(0, 2);
		int interval = adjustedRight / 2;
		int x, y, z;
		DIRECTION dir;
		DIRECTION dir2;
		ranSeed == 0 ? (x = LEFT,y = interval ,z = adjustedRight - interval,dir = DirRIGHTDOWN) : (x = LEFT + interval, y = adjustedRight, z  = -interval, dir = DirRIGHTUP);
		Coordinate startPoint(x, y, z);
		DrawStart(startPoint, points);
		startPoint = ranSeed == 0 ? startPoint.RightDown() : startPoint.RightUp();
		DrawStraightLine(AXISZ,dir,0,points, startPoint);
		DrawCorner(dir, DirRIGHT , points, startPoint);
		DrawStraightLine(AXISX, DirRIGHT, interval, points, startPoint);

		ranSeed = RandomInt(0, 2);
		dir = DirRIGHT;
		dir2 = ranSeed == 0 ? DirRIGHTDOWN : DirRIGHTUP;
		DrawCorner(dir, dir2,points,startPoint);
		
		//AXIS tempAx = ranSeed == 0 ? AXISX : AXISY;
		//int bound = ranSeed == 0 ? adjustedRight : LEFT;
		
		DrawStraightLine(AXISX, dir2, 16, points, startPoint);
		//DrawEnd(startPoint, points);

		/*
		reveal the river;
		*/
		shape = SFMLController::GenerateVertexArray(points);
		for (size_t i = 0; i < shape.getVertexCount(); ++i)
		{
			shape[i].color = RIVER_COLOR;
		}
		/*
		For debuggin check wheter there is some points missing or not
		*/
		//for (auto points : riverPoints)
		//{
		//	points->GetShape().setOutlineThickness(10);
		//	points->GetShape().setOutlineColor(BLACK);
		//}
		break;
	}
	case(ModeCIRCLE):
	{
		int startAxis = adjustedRight / 2;
		//upper circle
		Coordinate startPoint(-startAxis, startAxis, 0);
		DrawStraightLine(AXISZ, DirRIGHTUP, startAxis, points, startPoint);
		DrawCorner(DirRIGHTUP, DirRIGHT, points, startPoint);
		startPoint = startPoint.Right();
		DrawStraightLine(startAxis, DirRIGHT, points, startPoint);
		DrawCorner(DirRIGHT, DirRIGHTDOWN, points, startPoint);
		startPoint = startPoint.RightDown();
		DrawStraightLine(AXISZ, DirRIGHTDOWN, 0, points, startPoint);
		DrawCorner(DirRIGHTDOWN, DirLEFTDOWN, points, startPoint);
		DrawStraightLine(startAxis, DirLEFTDOWN, points, startPoint);
		DrawCorner(DirLEFTDOWN, DirLEFT, points, startPoint);
		DrawStraightLine(startAxis+1, DirLEFT, points, startPoint);
		DrawCorner(DirLEFT, DirLEFTUP, points, startPoint);
		startPoint = startPoint.LeftUp();
		DrawStraightLine(AXISZ, DirLEFTUP,  1 , points, startPoint);

		//shape = SFMLController::GenerateVertexArray(points);

		for (size_t i = 0; i < shape.getVertexCount(); ++i)
		{
			shape[i].color = RIVER_COLOR;
		}
		break;
		/*
		For debuggin check wheter there is some points missing or not
		*/
		//for (auto points : riverPoints)
		//{
		//	points->GetShape().setOutlineThickness(10);
		//	points->GetShape().setOutlineColor(BLACK);
		//}
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
		if (IsBoundaryOrNot(curCoord) == NODIRECTION)
		{
			MarkAsRiver(curCoord);
			switch (dir)
			{
			case(DirRIGHT):
			{
				inputList.InsertLast(curCoord.Up(1.02f*SIN60));
				inputList.InsertLast(curCoord.Down(1.02f*SIN60));
				curCoord = curCoord.Right();
				break;
			}
			case(DirRIGHTUP):
			{
				Draw(DirLEFT, DirRIGHT, curCoord, inputList);
				curCoord = curCoord.RightUp();
				break;
			}
			case(DirRIGHTDOWN):
			{
				Draw(DirRIGHT, DirLEFT, curCoord, inputList);
				curCoord = curCoord.RightDown();
				break;
			}
			case(DirLEFT):
			{
				inputList.InsertLast(curCoord.Down(1.02f*SIN60));
				inputList.InsertLast(curCoord.Up(1.02f*SIN60));
				curCoord = curCoord.Left();
				break;
			}
			case(DirLEFTUP):
			{
				Draw(DirLEFT, DirRIGHT, curCoord, inputList);
				curCoord = curCoord.LeftUp();
				break;
			}
			case(DirLEFTDOWN):
			{
				Draw(DirLEFT, DirRIGHT, curCoord, inputList);
				curCoord = curCoord.LeftDown();
				break;
			}

			default:
				break;
			}
			tempAx = ax == AXISX ? curCoord.X() : ax == AXISY ? curCoord.Y() : curCoord.Z();
		}
		else
		{
			DrawEnd(curCoord,inputList);
			break;
		}
		
	}
}
void River::DrawStraightLine(const int & distance, const DIRECTION & dir, List<Coordinate>& inputList, Coordinate & curCoord)
{
	for(int i = 0; i < distance;++i)
	{
		if (IsBoundaryOrNot(curCoord) == NODIRECTION)
		{
			MarkAsRiver(curCoord);
			switch (dir)
			{
			case(DirRIGHT):
			{
				inputList.InsertLast(curCoord.Up(1.02f*SIN60));
				inputList.InsertLast(curCoord.Down(1.02f*SIN60));
				curCoord = curCoord.Right();
				break;
			}
			case(DirRIGHTUP):
			{
				Draw(DirLEFT, DirRIGHT, curCoord, inputList);
				curCoord = curCoord.RightUp();
				break;
			}
			case(DirRIGHTDOWN):
			{
				Draw(DirRIGHT, DirLEFT, curCoord, inputList);
				curCoord = curCoord.RightDown();
				break;
			}
			case(DirLEFT):
			{
				inputList.InsertLast(curCoord.Down(1.02f*SIN60));
				inputList.InsertLast(curCoord.Up(1.02f*SIN60));
				curCoord = curCoord.Left();
				break;
			}
			case(DirLEFTUP):
			{
				Draw(DirLEFT, DirRIGHT, curCoord, inputList);
				curCoord = curCoord.LeftUp();
				break;
			}
			case(DirLEFTDOWN):
			{
				Draw(DirLEFT, DirRIGHT, curCoord, inputList);
				curCoord = curCoord.LeftDown();
				break;
			}

			default:
				break;
			}
		}
		else
		{
			DrawEnd(curCoord, inputList);
			break;
		}

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
/*
NODIRECTION means it is not the six Corner
Each Direction are using to represent one corner
*/
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
	int a1 = static_cast<int>(d1);
	int a2 = static_cast<int>(d2);
	int rotate = a2 - a1;
	if ((rotate == 1) || (rotate == -5))
	{
		int leftRo = a1 - 1;
		leftRo = ((a1 - 1) >= 0) ? (a1-1) : (6 + (a1 - 1));
		int rightRo = (a1 + 2) % 6;
		Draw(static_cast<DIRECTION>(leftRo), static_cast<DIRECTION>(rightRo), curCoord, inputList);
	}
	else if ((rotate == 2) || (rotate == -4))
	{

	}
	else if ((rotate == 4) || (rotate == -2))
	{

	}
	else if ((rotate == 5) || (rotate == -1))
	{
		int leftRo = a1 - 2;
		leftRo = ((a1 - 2) >= 0) ? (a1-2): (6 + (a1 - 2));
		int rightRo = (a1 + 1) % 6;
		Draw(static_cast<DIRECTION>(leftRo), static_cast<DIRECTION>(rightRo), curCoord, inputList);
	}
	else
	{
		throw std::out_of_range("Corner builder didn't cover all kind of situation");
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
			Draw(DirLEFTUP, DirRIGHTDOWN, coord, inputList);
			break;
		case DirRIGHT:
			Draw(DirLEFT, DirRIGHT, coord, inputList);
			break;
		case DirRIGHTDOWN:
			Draw(DirRIGHTUP, DirLEFTDOWN, coord, inputList);
			break;
		case DirLEFTDOWN:
			Draw(DirRIGHTDOWN, DirLEFTUP, coord, inputList);

			break;
		case DirLEFT:
			Draw(DirRIGHT, DirLEFT, coord, inputList);
			break;
		case DirLEFTUP:
			Draw(DirLEFTDOWN, DirRIGHTUP, coord, inputList);
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
			Draw(DirLEFT,DirRIGHTDOWN,coord,inputList);
			break;
		case DirRIGHT:
			Draw(DirLEFTUP, DirLEFTDOWN, coord, inputList);
			break;
		case DirRIGHTDOWN:
			Draw(DirRIGHTUP, DirLEFT, coord, inputList);
			break;
		case DirLEFTDOWN:
			Draw(DirRIGHT, DirLEFTUP, coord, inputList);
			break;
		case DirLEFT:
			Draw(DirRIGHTDOWN, DirRIGHTUP, coord, inputList);

			break;
		case DirLEFTUP:
			Draw(DirLEFTDOWN, DirRIGHT, coord, inputList);
			break;
		case NODIRECTION:
			break;
		default:
			break;
		}
	}
	return;
}

void River::DrawStart(const Coordinate & coord, List<Coordinate>& inputList)
{
	MarkAsRiver(coord);
	DIRECTION tempD = IsBoundaryOrNot(coord);
	switch (tempD)
	{
	case DirRIGHTUP:
		Draw(DirRIGHTDOWN, DirLEFTUP, coord, inputList);
		break;
	case DirRIGHT:
		Draw(DirRIGHT, DirLEFT, coord, inputList);
		break;
	case DirRIGHTDOWN:
		Draw(DirLEFTDOWN, DirRIGHTUP, coord, inputList);
		break;
	case DirLEFTDOWN:
		Draw(DirLEFTUP, DirRIGHTDOWN, coord, inputList);
		break;
	case DirLEFT:
		Draw(DirLEFT, DirRIGHT, coord, inputList);
		break;
	case DirLEFTUP:
		Draw(DirRIGHTUP, DirLEFTDOWN, coord, inputList);
		break;
	case NODIRECTION:
		break;
	default:
		break;
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
	if(! riverPoints.Contains(plotPtr))
		riverPoints.InsertLast(plotPtr);
}
