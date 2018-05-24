#pragma once
#include <SFML/Graphics.hpp>

/**
 * \brief Handles all UI rendering and initialization in game
 */
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

