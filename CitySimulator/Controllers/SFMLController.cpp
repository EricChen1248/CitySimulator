#include "SFMLController.h"
#include <iostream>
#include "CoreController.h"
#include "../Helpers/Constants.h"

using namespace sf;

/**
 * \brief  Gets the window of SDL controller
 * \return Reference to the window
 */
RenderWindow* const& SFMLController::Window() const
{
    return window;
}

void SFMLController::UpdateCircleSize(CircleShape& circle)
{
    const auto mod = CoreController::Instance()->GetViewportController()->Modifier();
    if (mod != 1)
    {
        circle.setRadius(circle.getRadius() * mod);
    }
}

/**
 * \brief Initializes window and renderer for sdl
 */
SFMLController::SFMLController() : isRunning(false), window(nullptr)
{
    InitSFML();
}


SFMLController::~SFMLController()
{
    window->close();
    std::cout << "SFML quit" << std::endl;
}

/**
 * \brief Check if SFMLController is running
 * \return True if the RenderWindow is open
 */
bool SFMLController::IsRunning() const
{
    return window->isOpen();
}

/**
 * \brief Wipes the pixel buffer white
 */
void SFMLController::ClearRender() const
{
    window->clear(WHITE);
    
}


/**
 * \brief Interface for drawing a circle to the RenderWindow
 * \param circle Circle to draw
 * \param isUi UI Flag, will not resize circle if is UI
 */
void SFMLController::DrawCircle(CircleShape& circle, const bool isUi) const
{
    if (!isUi)
    {
        UpdateCircleSize(circle);
    }
    
    window->draw(circle);
}

/**
 * \brief Draws a rectangle to the window
 * \param rectangle Rectangel to draw to screen
 * \param isUi UI Flag, will not resize rect if is UI
 */
void SFMLController::DrawRect(RectangleShape& rectangle, const bool isUi) const
{
    if (!isUi)
    {
        const auto mod = CoreController::Instance()->GetViewportController()->Modifier();
        if (mod != 1)
        {
            rectangle.setSize(rectangle.getSize() * mod);
        }
    }
    
    window->draw(rectangle);
}

void SFMLController::DrawLine(ConvexShape shape, const bool isUi) const
{
    if (!isUi)
    {
        const auto mod = CoreController::Instance()->GetViewportController()->Modifier();
        if (mod != 1)
        {
            shape.setOutlineThickness(shape.getOutlineThickness() * mod);
        }
    }
    
    window->draw(shape);    
}

void SFMLController::DrawShape(sf::Shape& shape) const
{
    window->draw(shape);
}

/**
 * \brief Draws a string to the window
 * \param text Text to draw to screen
 */
void SFMLController::DrawString(Text& text) const
{
    window->draw(text);
}

ConvexShape SFMLController::GenerateLine(const List<Plot*>& plots)
{
    ConvexShape shape;
    shape.setPointCount(plots.Count() * 2 - 1);
    
    const int count = plots.Count();
    for (int i = 0; i < count; ++i)
    {
        shape.setPoint(i, plots[i]->Coords().ToScreenCoordinates().ToVector2F());
    }
    
    for (int i = 0; i < count ; ++i)
    {
        shape.setPoint(i + count, plots[count - i]->Coords().ToScreenCoordinates().ToVector2F());
    }
    
    return shape;
}

ConvexShape SFMLController::GenerateLine(Plot* plot1, Plot* plot2)
{
    ConvexShape shape;
    shape.setPointCount(2);
    shape.setPoint(0, plot1->Coords().ToScreenCoordinates().ToVector2F());
    shape.setPoint(1, plot2->Coords().ToScreenCoordinates().ToVector2F());
    return shape;
}


/**
 * \brief Pushes the buffered pixels to the window
 */
void SFMLController::UpdateWindow() const
{
    window->display();
}

/**
 * \brief Initializes the SFML
 */
void SFMLController::InitSFML() 
{
    window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "City Simulator");
    window->setFramerateLimit(60);
    isRunning = true;
}