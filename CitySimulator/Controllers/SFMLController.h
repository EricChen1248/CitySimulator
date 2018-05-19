#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
class SFMLController
{
friend class CoreController;
public:
    RenderWindow* const& Window() const;

private:
    // Constructors and Destructors
    SFMLController();
    ~SFMLController();
    
    // Properties
    bool IsRunning() const;
    
    // Methods
    void InitSFML();
    void ClearRender() const;
    void Render(Drawable& shape) const;
    void PresentRender() const;
    
    // Backing variables
    bool isRunning;
    RenderWindow *window{};
};

