#include "Slider.h"
#include "../CoreController.h"
#include "../SFMLController.h"
#include "../FontController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/HelperFunctions.h"

const int Slider::MAX_RATE;

Slider::Slider(const Vector2f position, const Vector2f size, const int initialValue /* = 160 */) : value(initialValue), mouseClicked(false)
{
    background.setSize(Vector2f(size.x + 60, size.y));
    background.setPosition(position);
    background.setOutlineColor(BLACK);
    background.setOutlineThickness(2);
        
    leftBound = int(position.x + 5);
    rightBound = int(position.x + size.x - 15);
    centerLine.setSize(Vector2f(float(size.x - 10), 2.f));
    centerLine.setPosition(Vector2f(float(leftBound), position.y + size.y / 2.f));
    centerLine.setOutlineColor(BLACK);
    centerLine.setOutlineThickness(2);
        
    slider = new Button(Vector2f(10,size.y - 6), Vector2f(float(initialValue) * (rightBound - leftBound) / MAX_RATE + leftBound, centerLine.getPosition().y - (size.y - 6) / 2), WHITE, MOUSE_OVER_COLOR);
    
    text.setFont(FontController::Monofur());
    text.setPosition(position.x + size.x + 8, position.y + 5);
    text.setFillColor(BLACK);
    text.setCharacterSize(20);    
}

void Slider::Render()
{
    CoreController::SfmlController()->DrawShape(background);   
    CoreController::SfmlController()->DrawShape(centerLine);
    if (slider->Draw())
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mouseClicked = true;
        }
    }
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << float(value) / 100;
    text.setString(ss.str());
    CoreController::SfmlController()->DrawString(text);
    
    if (mouseClicked)
    {
        const sf::Window* window = CoreController::SfmlController()->Window();
        const auto &mousePos = sf::Mouse::getPosition(*window);
        const int x = Clamp(mousePos.x - 5, leftBound, rightBound);
        slider->SetPosition(Vector2f(float(x), centerLine.getPosition().y - (background.getSize().y - 6) / 2));
        value = (x - leftBound) * MAX_RATE / (rightBound - leftBound);        
        mouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
}

bool Slider::InBound() const
{
    const auto window = CoreController::SfmlController()->Window();
    const auto mousePos = sf::Mouse::getPosition(*window);
    return background.getGlobalBounds().contains(mousePos.x, mousePos.y);
}
