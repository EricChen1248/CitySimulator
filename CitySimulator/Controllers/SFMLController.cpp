#include "SFMLController.h"
#include <iostream>
#include "CoreController.h"
#include "../Helpers/Constants.h"

using namespace sf;

/**
 * \brief  Gets the window of SDL controller
 * \return Reference to the window
 */
RenderWindow* SFMLController::Window() const
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

void SFMLController::DrawShape(const VertexArray& array) const
{
    window->draw(array);
}

/**
 * \brief Draws a string to the window
 * \param text Text to draw to screen
 */
void SFMLController::DrawString(Text& text) const
{
    window->draw(text);
}

VertexArray SFMLController::GenerateVertexArray(const List<Coordinate>& coords)
{
	const int count = coords.Count();
    VertexArray shape(TriangleStrip, count);

	for (int i = 0; i < count; ++i)
	{
		shape[i].position = coords[i].ToScreenCoordinates().ToVector2F() + Vector2f(7,7);
	}
    
    return shape;
}

ConvexShape SFMLController::GenerateLine(const Coordinate& coord1, const Coordinate& coord2)
{
    ConvexShape shape;
    shape.setPointCount(2);
    shape.setPoint(0, coord1.ToScreenCoordinates().ToVector2F());
    shape.setPoint(1, coord2.ToScreenCoordinates().ToVector2F());
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