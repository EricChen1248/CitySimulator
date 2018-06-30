#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "../FontController.h"
#include "../../Helpers/Button.h"
#include "../../Helpers/Constants.h"

struct SelectionButton
{
    Button SelButton;
    sf::Text Text;
    sf::CircleShape Circle;
    SelectionButton(const Vector2f size,const Vector2f pos,const Color color, const Color moColor, const std::string& str, const int y, const Color circColor)
    {
        SelButton = Button(size, pos, color, moColor);
        
        Text.setFont(FontController::Monofur());
        Text.setFillColor(BLACK);
        Text.setCharacterSize(24U);
        Text.setPosition(WINDOW_WIDTH - 100.f, float(y));
        Text.setString(str); 
        
        Circle.setPosition(WINDOW_WIDTH - 146.f, y + 4.f);
        Circle.setRadius(12.f);
        Circle.setFillColor(circColor);
        Circle.setOutlineColor(BLACK);
        Circle.setOutlineThickness(1.f);
    }
    
    void Draw(SFMLController& sfml)
    {
        SelButton.Draw();  
        sfml.DrawString(Text);
        sfml.DrawShape(Circle);
    }
};
