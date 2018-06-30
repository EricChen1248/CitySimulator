#pragma once
#include <SFML/Graphics.hpp>
#include "../SFMLController.h"
#include "../../Helpers/Constants.h"
#include "../../Systems/SystemEnum.h"


struct SatisBar
{
	System Type;
	RectangleShape Shape;
	SatisBar(): Type(NONE)
    {
        Shape.setSize(Vector2f(148.f, 15.f));
    }
    ;
	SatisBar(const System sys) : Type(sys)
	{
		float multiple = static_cast<float>(Type) - 1;
		multiple = 38 + (55 * multiple);
		Shape.setPosition(WINDOW_WIDTH - 152.f, multiple);
		Shape.setFillColor(WHITE);
	};

	void Render(const float ratio)
	{
		if (ratio < 0.3)
		{
			Shape.setFillColor(UNSATISFIED_COLOR);
		}
		else if ((ratio >= 0.3) && (ratio < 0.7))
		{
			Shape.setFillColor(SATISFIED_COLOR);
		}
		else
		{
			Shape.setFillColor(SUPER_SATIFIED_COLOR);
		}
		
		Shape.setSize(Vector2f(148.f*ratio, 15.f));
		
		return;
	};
	void Draw(SFMLController& sfml) const
	{
		sfml.DrawShape(Shape);
	};

};
