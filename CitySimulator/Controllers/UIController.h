#pragma once
#include <SFML/Graphics.hpp>
#include "../Helpers/Button.h"
#include "SFMLController.h"
#include "../Collections/List.h"

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
	List<float>& getScoreList(){ return scoreList; };
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
    
	//TODO: Eric Please check, whether this is a good implment of Satisfactory revealing System
	RectangleShape food_S_Shape{};
	RectangleShape home_S_Shape{};
	List<float> scoreList ;

    void NextDayButton();
    void Time();
    void Money();
    void Selection();
	void Satisfaction();
    void InitSelection();
	void Init_Satisfaction();
    static void InitSelectionButton(Button& button, sf::Text& text, sf::CircleShape& circ, int& y, const std::string& str, Color color);
	sf::Color Satisfy(float ratio)const;
	SFMLController& sfml;
};

