#pragma once
#include <SFML/Graphics.hpp>
#include "../Helpers/Button.h"
#include "SFMLController.h"

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
    RectangleShape timeRect{};
    
    sf::Text moneyText{};
    RectangleShape moneyRect{};
    
    Button nextDay;
    RectangleShape nextDayShape{};
    RectangleShape nextDayMoShape{};
    sf::Text nextDayText{};
    
    RectangleShape selectionBackGround{};
    Button food;
    Button home;
    Button work;
    Button bank;
    sf::Text foodText{};
    sf::Text homeText{};
    sf::Text workText{};
    sf::Text bankText{};
    sf::CircleShape foodCirc{};
    sf::CircleShape homeCirc{};
    sf::CircleShape workCirc{};
    sf::CircleShape bankCirc{};
    
    void NextDayButton();
    void Time();
    void Money();
    void Selection();
    
    void InitSelection();
    static void InitSelectionButton(Button& button, sf::Text& text, sf::CircleShape& circle, int& y, const std::string& str, Color color);
    SFMLController& sfml;
};

