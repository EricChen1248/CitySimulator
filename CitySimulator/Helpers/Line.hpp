#pragma once
#include <SFML/Graphics.hpp>
#include "Coordinate.h"

using sf::Vector2f;

/**
 * \brief Draws a line with controllable thickness in SFML
 */
class Line
{
public:
    Line() = default;
    ~Line() = default;
    
    Line(const Coordinate& coord1, const Coordinate& coord2, const sf::Color color,
         const float thickness): thickness(thickness), color(color)
    {
        vertices = sf::VertexArray(sf::Quads, 4);
        bounds = sf::VertexArray(sf::Quads, 4);
        point1 = coord1.ToScreenCoordinates().ToVector2F();
        point2 = coord2.ToScreenCoordinates().ToVector2F();

        const Vector2f direction = point2 - point1;
        const Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        const Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

        offset = thickness / 2.f * unitPerpendicular;

        ChangeColor(color);
        ChangeThickness(thickness);
        
        bounds[0].position = point1 + offset * 5.f;
        bounds[1].position = point2 + offset * 5.f;
        bounds[2].position = point2 - offset * 5.f;
        bounds[3].position = point1 - offset * 5.f;
    }
    
    /**
     * \brief Draws the line to the window using SFML
     * \param window window to draw the line to
     */
    void Render(sf::RenderWindow* window) const
    {
        window->draw(vertices);
    }

    /**
     * \brief Changes the current thickness of the line
     * \param thickness New thickness of the line
     */
    void ChangeThickness(const float thickness)
    {
        offset /= this->thickness;
        this->thickness = thickness;
        offset *= thickness;

        vertices[0].position = point1 + offset;
        vertices[1].position = point2 + offset;
        vertices[2].position = point2 - offset;
        vertices[3].position = point1 - offset;
    }
    
    /**
     * \brief Permantly changes the color
     * \param color New color to set to
     */
    void SetColor(const sf::Color color)
    {
        this->color = color;
        ChangeColor(color);
    }
    
    /**
     * \brief Temporary changes the color of the line
     * \param color Color to change to
     */
    void ChangeColor(const sf::Color color)
    {
        for (int i = 0; i < 4; ++i)
        {
            vertices[i].color = color;
        }
    }
    
    /**
     * \brief Provides a non-minimal bounding check for preliminary collision detection
     * \param x x-axis position to check on
     * \param y y-axis position to check on
     * \return true if (x,y) is in simple bounds, else false
     */
    bool InSimpleBounds(const float x, const float y) const
    {
        return bounds.getBounds().contains(x, y);
    }
    
    /**
     * \brief Uses advanced point to line distance alogrithm for exact collision detection
     * \param x x-axis position to check on
     * \param y y-axis position to check on
     * \return true if (x,y) is in complex bounds, else false
     */
    bool InComplexBounds(const float x, const float y) const
    {
        const float y1 = point1.y, y2 = point2.y, x1 = point1.x, x2 = point2.x;
        const float numerator = (y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1;
        const float denom = pow(y2 - y1, 2) + pow(x2 - x1, 2);
        return pow(numerator, 2) / denom < pow(thickness * 10, 2);
    }
    
    /**
     * \brief Resets the temporary color to the assigned color
     */
    void ResetColor()
    {
        for (int i = 0; i < 4; ++i)
        {
            vertices[i].color = color;
        }
    }
    
private:
    Vector2f point1;
    Vector2f point2;
    Vector2f offset;
    sf::VertexArray vertices;
    sf::VertexArray bounds;
    float thickness{};
    sf::Color color;
};
