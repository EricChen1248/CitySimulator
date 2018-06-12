#include "Button.h"
#include <SFML/Window/Mouse.hpp>
#include "../Controllers/CoreController.h"


Button::Button()
= default;

Button::Button(const Vector2f size, const Vector2f pos, const Color color, const Color moColor) : color(color), moColor(moColor)
{
    shape.setSize(size);
    shape.setPosition(pos);
    shape.setOutlineColor(BLACK);
    shape.setOutlineThickness(2);
}

Button::~Button() = default;
/**
 * \brief Draws the button to the screen
 */
void Button::Draw()
{
    if (IsInBounds())
    {
        shape.setFillColor(moColor);
    }
    else
    {
        shape.setFillColor(color);
    }
    CoreController::Instance()->SfmlController()->DrawShape(shape);
}

/**
 * \brief Checks if the mouse is within the bounds (non-minimum) provided by SFML of the button
 * \return True if mouse is in the bounds of the button
 */
bool Button::IsInBounds() const
{   
    const sf::Window* window = CoreController::Instance()->SfmlController()->Window();
    const auto &mousePos = sf::Mouse::getPosition(*window);
    return shape.getGlobalBounds().contains(mousePos.x, mousePos.y);
}
