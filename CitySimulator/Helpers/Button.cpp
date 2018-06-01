#include "Button.h"
#include <SFML/Window/Mouse.hpp>
#include "../Controllers/CoreController.h"

Button::Button(Shape* shape, Shape* mouseOverShape)
{
    this->shape = shape;
    moShape = mouseOverShape;
}

Button::~Button()
{
    delete shape;
    delete moShape;
}

void Button::Draw() const
{
    if (moShape != nullptr)
    {
        if (IsInBounds())
        {
            CoreController::Instance()->SfmlController()->DrawShape(*moShape);
            return;
        }
    }
    CoreController::Instance()->SfmlController()->DrawShape(*shape);
}

bool Button::IsInBounds() const
{   
    const sf::Window* window = CoreController::Instance()->SfmlController()->Window();
    const auto &mousePos = sf::Mouse::getPosition(*window);
    return shape->getGlobalBounds().contains(mousePos.x, mousePos.y);
}
