#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
/**
 * \brief Handles all the interfacing with SFML
 */
class SFMLController
{
friend class CoreController;
public:
    RenderWindow* const& Window() const;

    static void UpdateCircleSize(CircleShape& circle);
    void DrawCircle(CircleShape& circle, bool isUi = false) const;
    void DrawRect(RectangleShape& rectangle, bool isUi = false) const;
    void DrawString(Text& text) const;
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

