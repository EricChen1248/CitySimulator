#pragma once
#include <SFML/Graphics.hpp>
#include "../../Collections/LinkedList.h"
#include "../Plot/Plot.h"
#include "../Plot/PlotSystem.h"
class River
{
public:
	River();
	~River();
	void Render() const;
	void Init();
private:
	sf::ConvexShape shape;
	
	List<Plot*> riverPoint;
	List<Plot*> leftBoundary;
	List <Plot*> rightBoundary;
	PlotSystem* plotSys;
	const int riverWidth = 2;
	void Init_Boundary();
};

