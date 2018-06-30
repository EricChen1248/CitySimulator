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
    Button(Vector2f size,Vector2f pos, Color color, Color moColor);
    ~Button();
    void Draw();
    bool IsInBounds() const;
    void SetPosition(Vector2f position);
private:
    RectangleShape shape;
    Color color;
    Color moColor;
};

