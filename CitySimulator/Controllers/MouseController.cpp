#include "MouseController.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

bool MouseController::clicked = false;

MouseController::MouseController()
= default;


MouseController::~MouseController()
= default;
void MouseController::Reset()
{
    clicked = false;
}

bool MouseController::IsClicked()
{
    return clicked;
}

void MouseController::Unclick(sf::Event& event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        clicked = true;
    }
}
