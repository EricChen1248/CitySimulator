#pragma once
#include <SFML/Graphics.hpp>
#include "../../Collections/List.h"
#include "../Plot/Plot.h"
#include "../RiverEnum.h"
class River
{
public:
	River();
	~River();
	void Render() const;
	void Init();
private:
	sf::VertexArray shape;
	
	List<Plot*> riverPoints;
	List<Plot*> leftBoundary;
	List <Plot*> rightBoundary;
	const int riverWidth = 2;
	void InitBoundary();
	void DrawStraightLine(const AXIS & ax, const DIRECTION & dir, const int & boundary, List<Coordinate>& inputList, Coordinate & curCoord);
	DIRECTION IsBoundaryOrNot(const Coordinate& coord)const;
	DIRECTION IsSixOrNot(const Coordinate& coord)const;
	void DrawCorner(DIRECTION d1, DIRECTION d2, List<Coordinate>& inputList, Coordinate& curCoord);
	void DrawEnd(const Coordinate& coord, List<Coordinate>& inputList);
	void Draw(const DIRECTION d1, const DIRECTION d2, const Coordinate & coord, List<Coordinate>& inputlist, float length = float(0.88));
	void MarkAsRiver(const Coordinate& coord);
};

