#pragma once
#include <SFML/Graphics.hpp>
#include "../SFMLController.h"
#include "../../Helpers/Constants.h"
#include "../../Systems/SystemEnum.h"
#include "../../Helpers/Constants.h"


struct SatisBar
{
	System system;
	sf::RectangleShape shape;
	SatisBar()
	{
		shape.setSize(sf::Vector2f(150.f, 32.f));
	};
	SatisBar(System sys)
	{
		system = sys;
		float multiple = static_cast<float>(system) - 1;
		multiple = 38 + (72 * multiple);
		shape.setPosition(WINDOW_WIDTH - 152.f, multiple);
		shape.setFillColor(WHITE);
	};

	void render(float ratio)
	{
		if (ratio < 0.3)
		{
			shape.setFillColor(UNSATISFIED_COLOR);
		}
		else if ((ratio >= 0.3) && (ratio < 0.7))
		{
			shape.setFillColor(SATISFIED_COLOR);
		}
		else
		{
			shape.setFillColor(SUPER_SATIFIED_COLOR);
		}
		shape.setSize(sf::Vector2f(150.f*ratio, 32.f));
		return;
	};
	void Draw(SFMLController& sfml)
	{
		sfml.DrawRect(shape);
	};

};
