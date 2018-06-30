#pragma once
#include <SFML/Graphics.hpp>
#include "../../Collections/List.h"
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
	List<Plot*> leftPoint;
	List<Plot*> rightPoint;
	List<Plot*> leftBoundary;
	List <Plot*> rightBoundary;
	PlotSystem* plotSys;
	const int riverWidth = 2;
	void Init_Boundary();
};

