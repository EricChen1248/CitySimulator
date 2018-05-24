#pragma once
#include <SFML/Graphics.hpp>
class UIController
{
public:
    UIController();
    ~UIController();
    
    void RenderUI();
private:
    sf::Text timeText{};
    sf::RectangleShape timeRect{};
    
    void Time();
};

