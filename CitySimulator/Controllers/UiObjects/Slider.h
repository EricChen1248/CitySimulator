#pragma once
#include <SFML/Graphics.hpp>
#include "../../Helpers/Button.h"
using sf::RectangleShape;

class Slider
{
public:
    Slider() = default;
    Slider(Vector2f position, Vector2f size, int initialValue = 80);
    void Render();
    int Value() const { return value; }
    
private:
    RectangleShape background;
    RectangleShape centerLine;
    sf::Text text;
    Button* slider{};
    int value{};
    int leftBound{};
    int rightBound{};
    bool mouseClicked{};
};