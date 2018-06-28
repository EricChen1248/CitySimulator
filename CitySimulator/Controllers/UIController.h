#pragma once
#include <SFML/Graphics.hpp>
#include "../Helpers/Button.h"
#include "SFMLController.h"
#include "../Collections/List.h"
#include "UiObjects/SelectionButton.h"

/**
 * \brief Handles all UI rendering and initialization in game
 */
class UIController
{
public:
    UIController();
    ~UIController();
    
    void Initialize();
    void RenderUI();
    void RenderInterDayUI();
    bool NextDayButtonHover() const { return nextDay.IsInBounds(); };
	List<float>& GetScoreList(){ return scoreList; };
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
    List<SelectionButton*> selectionButtons{};
    
	//TODO: Eric Please check, whether this is a good implment of Satisfactory revealing System
<<<<<<< HEAD
	RectangleShape food_S_Shape{};
	RectangleShape home_S_Shape{};
=======
	RectangleShape foodSShape{};
>>>>>>> ea653380d5075e2ece30a4fc74d13382d547f3ae
	List<float> scoreList ;

    void NextDayButton();
    void Time();
    void Money();
    void DrawSelection();
	void DrawSatisfaction();
    void InitSelection();
<<<<<<< HEAD
	void Init_Satisfaction();
    static void InitSelectionButton(Button& button, sf::Text& text, sf::CircleShape& circ, int& y, const std::string& str, Color color);
	sf::Color Satisfy(float ratio)const;
	SFMLController& sfml;
=======
	void InitSatisfaction();

    static SelectionButton* InitSelectionButton(int& y, const std::string& str, Color color);

    SFMLController& sfml;
>>>>>>> ea653380d5075e2ece30a4fc74d13382d547f3ae
};

