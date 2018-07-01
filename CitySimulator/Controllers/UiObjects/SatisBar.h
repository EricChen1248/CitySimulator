#pragma once
#include <SFML/Graphics.hpp>
#include "../SFMLController.h"
#include "../../Helpers/Constants.h"
#include "../../Systems/SystemEnum.h"


struct SatisBar
{
	System Type;
	sf::VertexArray Shape;
    RectangleShape Blank;
	SatisBar(): Type(NONE)
    {
    }
    
	SatisBar(const System sys) : Type(sys), Shape(sf::TriangleStrip, 4)
	{
		float multiple = static_cast<float>(Type) - 1;
		multiple = 38 + (55 * multiple);
	    Blank.setPosition(0, multiple);
	    Color colors[2] = {SATISFIED_COLOR, SUPER_SATIFIED_COLOR};
	    for (int i = 0; i < 4; i += 2)
	    {
	        Shape[i].position = Vector2f(WINDOW_WIDTH - 151.f + i * 74.f, multiple);
	        Shape[i].color = colors[i / 2];
	        Shape[i + 1].position = Vector2f(WINDOW_WIDTH - 151.f + i * 74.f, multiple + 15);
	        Shape[i + 1].color = colors[i / 2];
	    }
	    Blank.setFillColor(WHITE);
	}

	void Draw(const float ratio, SFMLController& sfml)
	{
	    const float x = 148.f * (1.f - ratio);
	    Blank.setSize(Vector2f(x, 15.f));
	    Blank.setPosition(WINDOW_WIDTH - 4.f - x, Blank.getPosition().y);
		
		sfml.DrawShape(Shape);
	    sfml.DrawShape(Blank);
	}

};
