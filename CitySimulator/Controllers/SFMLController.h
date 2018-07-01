#pragma once

#include "../Collections/List.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Coordinate;
class Plot;
/**
 * \brief Handles all the interfacing with SFML
 */
class SFMLController
{
friend class CoreController;
public:
    sf::RenderWindow* Window() const;
    
    void DrawShape(const sf::Shape& shape) const;
    void DrawShape(const sf::VertexArray& array) const;
    void DrawString(sf::Text& text) const;
    static sf::VertexArray GenerateVertexArray(const List<Coordinate>& coords);
    static sf::ConvexShape GenerateLine(const Coordinate& coord1, const Coordinate& coord2);
private:
    // Constructors and Destructors
    SFMLController();
    ~SFMLController();
    
    // Properties
    bool IsRunning() const;
    
    // Methods
    void InitSFML();
    void ClearRender() const;
    void UpdateWindow() const;
    
    // Backing variables
    bool isRunning{};
    sf::RenderWindow *window{};
};

