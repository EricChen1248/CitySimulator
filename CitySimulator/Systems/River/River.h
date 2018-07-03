#pragma once
#include <SFML/Graphics.hpp>
#include "../../Collections/List.h"
#include "../Plot/Plot.h"


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
	ModeACCROSS,
	ModeCIRCLE,
	NORIVER,
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


	//function
	void InitBoundary();
    static DIRECTION IsBoundaryOrNot(const Coordinate& coord);
    static DIRECTION IsSixOrNot(const Coordinate& coord);
	void DrawStart(const Coordinate& coord, List<Coordinate>& inputList);
	void DrawStraightLine(const AXIS ax, const DIRECTION dir, const int boundary, List<Coordinate>& inputList, Coordinate & curCoord);
	void DrawStraightLine(const int& distance, const DIRECTION& dir, List<Coordinate>& inputList, Coordinate& curCoord);
	void DrawCorner(DIRECTION d1, DIRECTION d2, List<Coordinate>& inputList, Coordinate& curCoord);
	void DrawEnd(const Coordinate& coord, List<Coordinate>& inputList);
	//Helper Function for avoiding funciton decoupling 
	void Draw(const DIRECTION d1, const DIRECTION d2, const Coordinate & coord, List<Coordinate>& inputlist, float length = float(0.88));
	void MarkAsRiver(const Coordinate& coord);
};
