#pragma once
#include <SFML/Graphics.hpp>
#include "../Plot/Plot.h"
#include "../../Collections/List.h"


enum DIRECTION
{
	DirRIGHTUP = 0,
	DirRIGHT,
	DirRIGHTDOWN,
	DirLEFTDOWN,
	DirLEFT,
	DirLEFTUP,
	NODIRECTION,
};
enum RIVERMODE
{
	ModeSTRAIGHT = 0,
	ModeCIRCLE,
	ModeACCROSS,
	ModeNORIVER,
	ModeALTIMATE,
};
enum AXIS
{
	AXISX,
	AXISY,
	AXISZ,
};

class River
{
public:
	River();
	~River();
	void Render() const;
	void Update();
	void Init();
private:
	sf::VertexArray shape;
	//Variable
	List<Plot*> riverPoints;
	List<Plot*> leftBoundary;
	List <Plot*> rightBoundary;
	List<Coordinate> points;
	int riverColorChange;
	float accumulatedTime;
	//for more than two river;
	sf::VertexArray shapeAltimate;
	List<Coordinate> pointsAltimate1;
	List<Coordinate> pointsAltimate2;

	//function
	void InitBoundary();
    static DIRECTION IsBoundaryOrNot(const Coordinate& coord);
    static DIRECTION IsSixOrNot(const Coordinate& coord);
	void DrawStart(const Coordinate& coord, List<Coordinate>& inputList);
	bool DrawStraightLine(const int& distance, const DIRECTION& dir, List<Coordinate>& inputList, Coordinate& curCoord);
	void DrawCorner(DIRECTION d1, DIRECTION d2, List<Coordinate>& inputList, Coordinate& curCoord);
	void DrawEnd(const Coordinate& coord, List<Coordinate>& inputList);
	//Helper Function for avoiding funciton decoupling 
    static void Draw(const DIRECTION d1, const DIRECTION d2, const Coordinate & coord, List<Coordinate>& inputlist, float length = float(0.88));
	void MarkAsRiver(const Coordinate& coord);
    static void MoveCoord(DIRECTION d1, Coordinate& coord);
	void DrawSmoothCorner(const Coordinate& center, const int& startDeg, const int& endDeg, const float innerL, const float outerL);
	
};
