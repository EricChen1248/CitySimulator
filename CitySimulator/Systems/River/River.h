#pragma once
#include <SFML/Graphics.hpp>
#include "../../Collections/List.h"
#include "../Plot/Plot.h"
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
};

