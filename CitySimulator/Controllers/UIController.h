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
	RectangleShape foodSShape{};
	List<float> scoreList ;

    void NextDayButton();
    void Time();
    void Money();
    void DrawSelection();
	void DrawSatisfaction();
    void InitSelection();
	void InitSatisfaction();

    static SelectionButton* InitSelectionButton(int& y, const std::string& str, Color color);

    SFMLController& sfml;
};

