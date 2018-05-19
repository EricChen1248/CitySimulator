#include "SFMLController.h"
#include <iostream>


/**
 * \brief  Gets the window of SDL controller
 * \return Reference to the window
 */
RenderWindow* const& SFMLController::Window() const
{
    return window;
}

/**
 * \brief Initializes window and renderer for sdl
 */
SFMLController::SFMLController()
{
    window = nullptr;    
    InitSFML();
}


SFMLController::~SFMLController()
{
    window->close();
    std::cout << "SFML quit" << std::endl;
}

bool SFMLController::IsRunning() const
{
    return window->isOpen();
}

/**
 * \brief 
 */
void SFMLController::ClearRender() const
{
    window->clear(Color::White);
    
}

void SFMLController::Render(Drawable& shape) const
{
    window->draw(shape);
}

void SFMLController::PresentRender() const
{
    window->display();
}

/**
 * \brief Initializes the SDL
 */
void SFMLController::InitSFML() 
{
    window = new RenderWindow(VideoMode(1024, 768), "SFML works!");
    window->setFramerateLimit(60);
    isRunning = true;
}