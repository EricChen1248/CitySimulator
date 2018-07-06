#include "MouseController.h"
#include <SFML/Window/Mouse.hpp>

bool MouseController::mousePressed = false;

MouseController::MouseController()
= default;


MouseController::~MouseController()
= default;

bool MouseController::IsClicked()
{
    if (!mousePressed)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mousePressed = true;
        }
    }
    else
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mousePressed = false;
            return true;
        }
    }
    return false;
}
