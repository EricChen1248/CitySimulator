#pragma once
#include <SFML/Graphics.hpp>
#include "Coordinate.h"

using sf::Vector2f;

class Line
{
public:
    Line() = default;

    void Render(sf::RenderWindow* window) const
    {
        window->draw(vertices, 4, sf::Quads);
    }

    void ChangeThickness(const float thickness)
    {
        offset *= this->thickness;
        this->thickness = thickness;
        offset *= thickness;

        vertices[0].position = point1 + offset;
        vertices[1].position = point2 + offset;
        vertices[2].position = point2 - offset;
        vertices[3].position = point1 - offset;
    }

    void ChangeColor(const sf::Color color)
    {
        for (auto& vertice : vertices)
        {
            vertice.color = color;
        }
    }

    Line(const Coordinate& coord1, const Coordinate& coord2, const sf::Color color,
         const float thickness): thickness(thickness), color(color)
    {
        point1 = coord1.ToScreenCoordinates().ToVector2F();
        point2 = coord2.ToScreenCoordinates().ToVector2F();

        const Vector2f direction = point2 - point1;
        const Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        const Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

        offset = (thickness / 2.f) * unitPerpendicular;

        ChangeColor(color);
        ChangeThickness(thickness);
    }
    
    ~Line() = default;
private:
    Vector2f point1;
    Vector2f point2;
    Vector2f offset;
    sf::Vertex vertices[4];
    float thickness{};
    sf::Color color;
};
