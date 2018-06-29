#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "../Collections/List.h"

class Plot;
/**
 * \brief Handles all the interfacing with SFML
 */
class SFMLController
{
friend class CoreController;
public:
    sf::RenderWindow* const& Window() const;
    
    void DrawShape(const sf::Shape& shape) const;
    void DrawString(sf::Text& text) const;
    static sf::ConvexShape GenerateConvex(const List<Plot*>& plots);
    static sf::ConvexShape GenerateLine(Plot* plot1, Plot* plot2);
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

