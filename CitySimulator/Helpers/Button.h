#pragma once
#include <SFML/Graphics/Shape.hpp>

using sf::Shape;
class Button
{
public:
    Button(Shape* shape, Shape* mouseOverShape = nullptr);
    ~Button();
    void Draw() const;
    bool IsInBounds() const;
private:
    Shape* shape;
    Shape* moShape;
};

