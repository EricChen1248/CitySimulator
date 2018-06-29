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
 * \brief Interface for drawing a shape to the RenderWindow
 * \param shape Shape to draw
 */
void SFMLController::DrawShape(const Shape& shape) const
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

ConvexShape SFMLController::GenerateConvex(const List<Plot*>& plots)
{
    ConvexShape shape;
	const int count = plots.Count();
    shape.setPointCount(count);

	for (int i = 0; i < count; ++i)
	{
		shape.setPoint(i, plots[i]->Coords().ToScreenCoordinates().ToVector2F());
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