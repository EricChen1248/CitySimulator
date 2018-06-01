#pragma once
#include <SFML/Graphics/Shape.hpp>

using sf::Shape;
/**
 * \brief Middle interface between SFML and code base that provides draw and bounds check capabilities.
 */
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

