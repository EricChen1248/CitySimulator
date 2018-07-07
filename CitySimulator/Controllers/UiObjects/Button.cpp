#include "Button.h"
#include <SFML/Window.hpp>
#include "../../Helpers/Constants.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SFMLController.h"


Button::Button()
= default;

Button::Button(const Vector2f size, const Vector2f pos, const Color& color, const Color& moColor) : color(color), moColor(moColor)
{
    shape.setSize(size);
    shape.setPosition(pos);
    shape.setOutlineColor(BLACK);
    shape.setOutlineThickness(2);
}

Button::~Button() = default;

void Button::ChangeColor(const Color& color, const Color& moColor)
{
    this->color = color;
    this->moColor = moColor;
}

void Button::ReverseColor()
{
    const Color t = color;
    color = moColor;
    moColor = t;
}

/**
 * \brief Draws the button to the screen
 */
bool Button::Draw()
{
    if (disable)
    {
        shape.setFillColor(DARK_GREY);
        CoreController::SfmlController()->DrawShape(shape);
        disable = false;
        return false;
    }
    
    const bool inBounds = IsInBounds();
    if (inBounds || disable)
    {
        shape.setFillColor(moColor);
    }
    else
    {
        shape.setFillColor(color);
    }
    CoreController::SfmlController()->DrawShape(shape);
    return inBounds;
}

/**
 * \brief Checks if the mouse is within the bounds (non-minimum) provided by SFML of the button
 * \return True if mouse is in the bounds of the button
 */
bool Button::IsInBounds() const
{   
    const sf::Window* window = CoreController::SfmlController()->Window();
    const auto &mousePos = sf::Mouse::getPosition(*window);
    return shape.getGlobalBounds().contains(float(mousePos.x), float(mousePos.y));
}

void Button::SetPosition(const Vector2f position)
{
    shape.setPosition(position);
}
