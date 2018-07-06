#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

using sf::RectangleShape;
using sf::Vector2f;
using sf::Color;
/**
 * \brief Middle interface between SFML and code base that provides draw and bounds check capabilities.
 */


class Button
{
public:
    Button();
    Button(Vector2f size,Vector2f pos, const Color& color, const Color& moColor);
    ~Button();
    void ChangeColor(const Color& color, const Color& moColor);
    void ReverseColor();
    bool Draw();
    bool IsInBounds() const;
    void SetPosition(Vector2f position);
private:
    RectangleShape shape;
    Color color;
    Color moColor;
};

