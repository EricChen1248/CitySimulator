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

    void DrawCircle(CircleShape& circle) const;
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
    RenderWindow *window{};
};

