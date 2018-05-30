#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

/**
 * \brief Handles all the interfacing with SFML
 */
class SFMLController
{
friend class CoreController;
public:
    sf::RenderWindow* const& Window() const;

    static void UpdateCircleSize(sf::CircleShape& circle);
    void DrawCircle(sf::CircleShape& circle, bool isUi = false) const;
    void DrawRect(sf::RectangleShape& rectangle, bool isUi = false) const;
    void DrawString(sf::Text& text) const;
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

