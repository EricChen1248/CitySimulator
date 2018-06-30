#pragma once
#include <SFML/Graphics.hpp>
#include "../Helpers/Button.h"
#include "SFMLController.h"
#include "../Collections/List.h"
#include "UiObjects/SelectionButton.h"
#include "UiObjects/SatisBar.h"
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
     
    RectangleShape statusRect{}; 
    
    RectangleShape selectionBackGround{};
    List<SelectionButton*> selectionButtons{};
	List<SatisBar*> satisfyBar{};

	//TODO: Eric Please check, whether this is a good implment of Satisfactory revealing System

	List<float> scoreList ;

    void NextDayButton();
    void Time();
    void Money();
    void DrawSelection();  
    void DrawSatisfaction() const; 
    void DrawStatus(); 
    void InitSelection();

	void InitSatisfaction();
	SFMLController& sfml;

    static SelectionButton* InitSelectionButton(int& y, const std::string& str, Color color);

};

