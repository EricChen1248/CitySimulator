#include "River.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/FeatureFlags.h"
#include<iostream>
River::River() : riverColorChange(0), accumulatedTime(0) {};

void River::Init()
{
    const auto& plots = CoreController::GetSystemController()->Plots();
    const int adjustedRight = RIGHT - 1;
    const int rand = RandomInt(1, adjustedRight - 1);


	//Mode 0 : straight river cuting city into half; Mode 1: cutting it vertically 
	RIVERMODE mode = static_cast<RIVERMODE>(Clamp(RandomInt(0, 10), 0, 2));
#if NO_RIVER
	mode = ModeNORIVER;
#endif

	switch (mode)
	{
	case(ModeSTRAIGHT):
	{
		InitBoundary();
		Coordinate startPoint(rand, adjustedRight - rand, LEFT);
		int random = RandomInt(0, 2);
		int random2 = random;
		while (startPoint.Z() < adjustedRight)
		{
			auto plotPtr = plots->FindPlot(startPoint);
			riverPoints.InsertLast(plotPtr);
			plotPtr->MarkAsRiver();
			points.InsertLast(startPoint.Right(float(0.88)));
			points.InsertLast(startPoint.Left(float(0.88)));

			startPoint = random == 0 ? startPoint.LeftUp() : startPoint.RightUp();
			if (rightBoundary.Contains(plotPtr))
			{
				random = 0;
			}
			else if (leftBoundary.Contains(plotPtr))
			{
				random = 1;
			}
			//0 goes left, 1 goes right
			
			random2 = random;
			random = RandomInt(0, 2);
		}
		break;

	}
	case(ModeACCROSS):
	{

		int interval = adjustedRight / 4;
		int ranSeed = RandomInt(0, 2);
		int ranPos = RandomInt(interval, adjustedRight - interval);
		int startX, startY, startZ;
		ranSeed == 0 ? (startX = LEFT,startY = ranPos,startZ = adjustedRight-ranPos) : (startX = -ranPos,startY =adjustedRight,startZ = LEFT + ranPos);
		Coordinate startPoint(startX, startY, startZ);

		//setting up for while loop
		bool stopFlag = false;
		DIRECTION randomDir1 = static_cast<DIRECTION>((static_cast<int>(IsBoundaryOrNot(startPoint))+3)%6);
		DIRECTION	randomDir2;
		int randomDis = RandomInt(2, adjustedRight / 2);
		DrawStart(startPoint, points);
		startPoint = randomDir1 == DirRIGHTUP ? startPoint.RightUp() : startPoint.RightDown();
		stopFlag = DrawStraightLine(randomDis, randomDir1, points, startPoint);
		while (!stopFlag)
		{
			randomDir2 = randomDir1;
			randomDir1 = static_cast<DIRECTION>(RandomInt(0, 3));
			std::cout << randomDir1 << std::endl;
			if (randomDir2 != randomDir1)
			{
				DrawCorner(randomDir2, randomDir1, points, startPoint);
			}
			stopFlag = DrawStraightLine(randomDis, randomDir1, points, startPoint);
		}
		break;

	}
	case(ModeCIRCLE):
	{
		int startAxis = adjustedRight / 2;
		//upper circle
		Coordinate startPoint(-startAxis, startAxis, 0);
		DrawStraightLine(startAxis, DirRIGHTUP, points, startPoint);
		DrawCorner(DirRIGHTUP, DirRIGHT, points, startPoint);
		DrawStraightLine(startAxis-1, DirRIGHT, points, startPoint);
		DrawCorner(DirRIGHT, DirRIGHTDOWN, points, startPoint);

		DrawStraightLine(startAxis-1,DirRIGHTDOWN, points, startPoint);
		DrawCorner(DirRIGHTDOWN, DirLEFTDOWN, points, startPoint);

		DrawStraightLine(startAxis-1, DirLEFTDOWN, points, startPoint);
		DrawCorner(DirLEFTDOWN, DirLEFT, points, startPoint);

		DrawStraightLine(startAxis-1, DirLEFT, points, startPoint);
		DrawCorner(DirLEFT, DirLEFTUP, points, startPoint);

		DrawStraightLine(startAxis-1, DirLEFTUP, points, startPoint);
		DrawCorner(DirLEFTUP, DirRIGHTUP, points, startPoint);
		break;

	}

	default:
		break;
	}
	//DEBUG

	shape = SFMLController::GenerateVertexArray(points);

	for (size_t i = 0; i < shape.getVertexCount(); ++i)
	{
		(i % 4 <= 1) ? shape[i].color = RIVER_COLOR : shape[i].color = RIVER_COLOR_2;
	}



}

River::~River()
= default;

void River::Render() const
{
    CoreController::SfmlController()->DrawShape(shape);
}

void River::Update()
{

    accumulatedTime += CoreController::Instance()->GetDeltaTime() * 1000;
    if (accumulatedTime >= 250)
    {
        riverColorChange = riverColorChange == 0 ? 1 : 0;
        accumulatedTime = 0;
    }
    for (size_t i = 0; i < shape.getVertexCount(); ++i)
    {
		(i + riverColorChange) % 4 <= 1 ? (shape[i].color = RIVER_COLOR) : (shape[i].color = RIVER_COLOR_2);
    }
}

void River::InitBoundary()
{
    const auto& plots = CoreController::GetSystemController()->Plots();

    const int adjustedRight = RIGHT - 1;

    Coordinate leftStartPoint(0, adjustedRight, LEFT);
    Coordinate rightStartPoint((adjustedRight - 1), (1), LEFT);
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

void River::DrawStraightLine(const AXIS ax, const DIRECTION dir, const int boundary, List<Coordinate>& inputList,
                             Coordinate& curCoord)
{
    int tempAx = ax == AXISX ? curCoord.X() : ax == AXISY ? curCoord.Y() : curCoord.Z();
    while (tempAx != boundary)
    {
        if (IsBoundaryOrNot(curCoord) == NODIRECTION)
        {
            MarkAsRiver(curCoord);
            switch (dir)
            {
            case DirRIGHT:
                {
                    inputList.InsertLast(curCoord.Up(1.02f * SIN60));
                    inputList.InsertLast(curCoord.Down(1.02f * SIN60));
                    curCoord = curCoord.Right();
                    break;
                }
            case DirRIGHTUP:
                {
                    Draw(DirLEFT, DirRIGHT, curCoord, inputList);
                    curCoord = curCoord.RightUp();
                    break;
                }
            case DirRIGHTDOWN:
                {
                    Draw(DirRIGHT, DirLEFT, curCoord, inputList);
                    curCoord = curCoord.RightDown();
                    break;
                }
            case DirLEFT:
                {
                    inputList.InsertLast(curCoord.Down(1.02f * SIN60));
                    inputList.InsertLast(curCoord.Up(1.02f * SIN60));
                    curCoord = curCoord.Left();
                    break;
                }
            case DirLEFTUP:
                {
                    Draw(DirLEFT, DirRIGHT, curCoord, inputList);
                    curCoord = curCoord.LeftUp();
                    break;
                }
            case DirLEFTDOWN:
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
            DrawEnd(curCoord, inputList);
            break;
        }
    }
}

bool River::DrawStraightLine(const int& distance, const DIRECTION& dir, List<Coordinate>& inputList,
                             Coordinate& curCoord)
{
    for (int i = 0; i < distance; ++i)
    {
        if (IsBoundaryOrNot(curCoord) == NODIRECTION)
        {
            MarkAsRiver(curCoord);
            switch (dir)
            {
            case DirRIGHT:
                {
					Draw(DirLEFTUP, DirRIGHTDOWN, curCoord, inputList);
                    curCoord = curCoord.Right();
                    break;
                }
            case DirRIGHTUP:
                {
                    Draw(DirLEFT, DirRIGHT, curCoord, inputList);
                    curCoord = curCoord.RightUp();
                    break;
                }
            case DirRIGHTDOWN:
                {
                    Draw(DirRIGHT, DirLEFT, curCoord, inputList);
                    curCoord = curCoord.RightDown();
                    break;
                }
            case DirLEFT:
                {
					Draw(DirRIGHTDOWN, DirLEFTUP, curCoord, inputList);
                    curCoord = curCoord.Left();
                    break;
                }
            case DirLEFTUP:
                {
                    Draw(DirLEFT, DirRIGHT, curCoord, inputList);
                    curCoord = curCoord.LeftUp();
                    break;
                }
            case DirLEFTDOWN:
                {
                    Draw(DirRIGHT,DirLEFT, curCoord, inputList);
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
			return true;
            break;
        }
    }
	if (IsBoundaryOrNot(curCoord) != NODIRECTION)
	{
		DrawEnd(curCoord, inputList);
		return true;
	}
	return false;
}

/*
NODIRECTION means it is not boundary
DirRight = means up
DirLEFT means down
*/
DIRECTION River::IsBoundaryOrNot(const Coordinate& coord)
{
    switch (coord.X())
    {
    case RIGHT - 1:
        return DirRIGHTDOWN;
    case LEFT:
        return DirLEFTUP;
    default: break;
    }
    
    switch (coord.Y())
    {
    case RIGHT - 1:
        return DirLEFTDOWN;
    case LEFT:
        return DirRIGHTUP;
    default: break;
    }
    
    switch (coord.Z())
    {
    case RIGHT - 1:
        return DirRIGHT;
    case LEFT:
        return DirLEFT;
    default: break;
    }
    return NODIRECTION;
}

/*
NODIRECTION means it is not the six Corner
Each Direction are using to represent one corner
*/
DIRECTION River::IsSixOrNot(const Coordinate& coord)
{
    if (coord.X() == LEFT && coord.Z() == RIGHT - 1)
    {
        return DirLEFTUP;
    }
    if (coord.Y() == LEFT && coord.Z() == RIGHT - 1)
    {
        return DirRIGHTUP;
    }
    if (coord.X() == RIGHT - 1 && coord.Y() == LEFT)
    {
        return DirRIGHT;
    }
    if (coord.X() == RIGHT - 1 && coord.Z() == LEFT)
    {
        return DirRIGHTDOWN;
    }
    if (coord.Y() == RIGHT - 1 && coord.Z() == LEFT)
    {
        return DirLEFTDOWN;
    }
    if (coord.X() == LEFT && coord.Y() == RIGHT - 1)
    {
        return DirLEFT;
    }
    return NODIRECTION;
}

void River::DrawCorner(const DIRECTION d1, const DIRECTION d2, List<Coordinate>& inputList, Coordinate& curCoord)
{
    MarkAsRiver(curCoord);
    int a1 = static_cast<int>(d1);
    int a2 = static_cast<int>(d2);
    int rotate = a2 - a1;
    if (rotate == 1 || rotate == -5)
    {
        int leftRo = a1 - 1;
        leftRo = a1 - 1 >= 0 ? a1 - 1 : 6 + (a1 - 1);
        int rightRo = (a1 + 2) % 6;
        Draw(static_cast<DIRECTION>(leftRo), static_cast<DIRECTION>(rightRo), curCoord, inputList);
		MoveCoord(d2, curCoord);
    }
    else if (rotate == 2 || rotate == -4) 
	{
		int leftRo = a1 - 2;
		leftRo = a1 - 2 >= 0 ? a1 - 2 : 6 + (a1 - 2);
		int rightRo = (a1 + 1) % 6;
		Draw(static_cast<DIRECTION>(leftRo), static_cast<DIRECTION>(rightRo), curCoord, inputList);
		MoveCoord(static_cast<DIRECTION>((static_cast<int>(d1) + 2) % 6), curCoord);
	}
    else if (rotate == 4 || rotate == -2) 
	{
	}
    else if (rotate == 5 || rotate == -1)
    {
        int leftRo = a1 - 2;
        leftRo = a1 - 2 >= 0 ? a1 - 2 : 6 + (a1 - 2);
        int rightRo = (a1 + 1) % 6;
        Draw(static_cast<DIRECTION>(leftRo), static_cast<DIRECTION>(rightRo), curCoord, inputList);
		MoveCoord(d2, curCoord);
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
            Draw(DirLEFT, DirRIGHTDOWN, coord, inputList);
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
            
        default:
            break;
        }
    }
    return;
}

void River::DrawStart(const Coordinate& coord, List<Coordinate>& inputList)
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

void River::Draw(const DIRECTION d1, const DIRECTION d2, const Coordinate& coord, List<Coordinate>& inputlist,
                 float length)
{
    switch (d1)
    {
    case DirLEFT:
        inputlist.InsertLast(coord.Left(length));
        break;
    case DirLEFTDOWN:
        inputlist.InsertLast(coord.LeftDown(length));
        break;
    case DirLEFTUP:
        inputlist.InsertLast(coord.LeftUp(length));
        break;
    case DirRIGHT:
        inputlist.InsertLast(coord.Right(length));
        break;
    case DirRIGHTDOWN:
        inputlist.InsertLast(coord.RightDown(length));
        break;
    case DirRIGHTUP:
        inputlist.InsertLast(coord.RightUp(length));
        break;
    default:
        break;
    }
    switch (d2)
    {
    case DirLEFT:
        inputlist.InsertLast(coord.Left(length));
        break;
    case DirLEFTDOWN:
        inputlist.InsertLast(coord.LeftDown(length));
        break;
    case DirLEFTUP:
        inputlist.InsertLast(coord.LeftUp(length));
        break;
    case DirRIGHT:
        inputlist.InsertLast(coord.Right(length));
        break;
    case DirRIGHTDOWN:
        inputlist.InsertLast(coord.RightDown(length));
        break;
    case DirRIGHTUP:
        inputlist.InsertLast(coord.RightUp(length));
        break;
    default:
        break;
    }
    return;
}

void River::MarkAsRiver(const Coordinate& coord)
{
    auto plotPtr = CoreController::GetSystemController()->Plots()->FindPlot(coord);
    plotPtr->MarkAsRiver();
    if (! riverPoints.Contains(plotPtr))
        riverPoints.InsertLast(plotPtr);
}

void River::MoveCoord(DIRECTION d1, Coordinate & coord)
{
	switch (d1)
	{
	case DirRIGHTUP:
		coord = coord.RightUp();
		break;
	case DirRIGHT:
		coord = coord.Right();
		break;
	case DirRIGHTDOWN:
		coord = coord.RightDown();
		break;
	case DirLEFTDOWN:
		coord = coord.LeftDown();
		break;
	case DirLEFT:
		coord = coord.Left();
		break;
	case DirLEFTUP:
		coord = coord.LeftUp();
		break;
	case NODIRECTION:
		break;
	default:
		break;
	}
	return;
}

void River::DrawSmoothCorner(const Coordinate & center, const float & startDeg, const float & endDeg, const float & innerL , const float & outerL )
{


	for (int i = startDeg; i < endDeg; ++i)
	{
		float sin_VECTOR = sin(2.f*PI*float(i%360) / 360.f);
		float cos_VECTOR = cos(2.f*PI*float(i%360) / 360.f);

		float coord_x = (outerL * sin_VECTOR*(-0.5f)) + (outerL * cos_VECTOR*(1.f));
		float coord_y = (outerL * sin_VECTOR*(-0.5f)) + (outerL * cos_VECTOR*(-1.f));
		float coord_z = (outerL * sin_VECTOR*(1.f));
		float coord_x1 = (innerL * sin_VECTOR*(-0.5f)) + (innerL * cos_VECTOR*(1.f));
		float coord_y1 = (innerL * sin_VECTOR*(-0.5f)) + (innerL * cos_VECTOR*(-1.f));
		float coord_z1 = (innerL * sin_VECTOR*(1.f));
		Coordinate outerCoord(float(center.X())+coord_x, float(center.Y())+coord_y, float(center.Z())+ coord_z);
		Coordinate innerCoord(float(center.X()) + coord_x1, float(center.Y()) + coord_y1, float(center.Z()) + coord_z1);
		points.InsertLast(outerCoord);
		points.InsertLast(innerCoord);
	}

}

