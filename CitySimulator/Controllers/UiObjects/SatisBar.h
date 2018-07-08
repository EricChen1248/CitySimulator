#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "../SFMLController.h"
#include "../../Helpers/Constants.h"
#include "../../Systems/SystemEnum.h"
#include "../../Helpers/HelperFunctions.h"


struct SatisBar
{
    SatisBar();
    SatisBar(System sys);
    void Draw(float targetRatio, SFMLController& sfml);

private:
    System type;
    sf::VertexArray shape;
    RectangleShape blank;
    float value;
};

inline SatisBar::SatisBar(): type(NONE), value(0) { }

inline SatisBar::SatisBar(const System sys): type(sys), shape(sf::TriangleStrip, 4), value(0)
{
    float multiple = static_cast<float>(type) - 1;
    multiple = 38 + (55 * multiple);
    blank.setPosition(0, multiple);
    Color colors[2] = {SATISFIED_COLOR, SUPER_SATIFIED_COLOR};
    for (int i = 0; i < 4; i += 2)
    {
        shape[i].position = Vector2f(WINDOW_WIDTH - 151.f + i * 74.f, multiple);
        shape[i].color = colors[i / 2];
        shape[i + 1].position = Vector2f(WINDOW_WIDTH - 151.f + i * 74.f, multiple + 15);
        shape[i + 1].color = colors[i / 2];
    }
    blank.setFillColor(WHITE);
}

inline void SatisBar::Draw(const float targetRatio, SFMLController& sfml)
{
    if (value > targetRatio)
    {
        value = Clamp(value - 0.01f, targetRatio, 1.f);
    }
    else if (value < targetRatio)
    {
        value = Clamp(value + 0.01f, 0.f, targetRatio);
    }

    const float x = 148.f * (1.f - value);
    blank.setSize(Vector2f(x, 15.f));
    blank.setPosition(WINDOW_WIDTH - 4.f - x, blank.getPosition().y);

    sfml.DrawShape(shape);
    sfml.DrawShape(blank);
}
