#pragma once
#include <SFML/Graphics.hpp>
#include "../Helpers/Button.h"

/**
 * \brief Handles all UI rendering and initialization in game
 */
class UIController
{
public:
    UIController();
    ~UIController();
    
    void RenderUI();
    void RenderInterDayUI();
    bool NextDayButtonHover() const { return nextDay.IsInBounds(); };
private:
    sf::Text timeText{};
    sf::RectangleShape timeRect{};
    
    Button nextDay;
    sf::RectangleShape nextDayShape{};
    sf::RectangleShape nextDayMoShape{};
    sf::Text nextDayText{};
    
    void NextDayButton();
    void Time();
};

