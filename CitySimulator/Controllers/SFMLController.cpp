#include "SFMLController.h"
#include "CoreController.h"
#include "../Helpers/Constants.h"
#include "../Helpers/Coordinate.h"

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
 * \brief Initializes window and renderer for sfmll
 */
SFMLController::SFMLController() : isRunning(false), window(nullptr)
{
    window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "City Simulator", Style::Titlebar | Style::Close);
    window->setFramerateLimit(60);
    isRunning = true;
    
    auto origin = Coordinate(0,0,0);
    playfield.resize(6);
    playfield.setPrimitiveType(TriangleStrip);
    playfield[0].position = origin.LeftDown(16).ToScreenCoordinates().ToVector2F();
    playfield[1].position = origin.RightDown(16).ToScreenCoordinates().ToVector2F();
    playfield[2].position = origin.Left(16).ToScreenCoordinates().ToVector2F();
    playfield[3].position = origin.Right(16).ToScreenCoordinates().ToVector2F();
    playfield[4].position = origin.LeftUp(16).ToScreenCoordinates().ToVector2F();
    playfield[5].position = origin.RightUp(16).ToScreenCoordinates().ToVector2F();
    for (int i = 0; i < 6; ++i)
    {
        playfield[i].color = WHITE;
    }
}

SFMLController::~SFMLController()
{
    window->close();
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
    window->clear(BACKGROUND);
    window->draw(playfield);
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
 * \brief Interface for drawing a vertexArray to the RenderWindow
 * \param array Vertex arrya being drawn
 */
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

/**
 * \brief Generates a vertex array from an alternating list of coordinates (Left Right Left Right coords)
 * \param coords List of coordinates of the vertex array
 * \return The generated vertex array
 */
VertexArray SFMLController::GenerateVertexArray(const List<Coordinate>& coords)
{
    const int count = coords.Count();
    VertexArray shape(TriangleStrip, count);

    for (int i = 0; i < count; ++i)
    {
        shape[i].position = coords[i].ToScreenCoordinates().ToVector2F();
    }

    return shape;
}

/**
 * \brief Pushes the buffered pixels to the window
 */
void SFMLController::UpdateWindow() const
{
    window->display();
}

