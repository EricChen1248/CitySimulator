#pragma once
#include <SFML/Graphics.hpp>
#include "../Helpers/Button.h"
#include "SFMLController.h"
#include "../Collections/List.h"
#include "UiObjects/SelectionButton.h"
#include "UiObjects/SatisBar.h"
#include "UiObjects/Slider.h"

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
     
    Slider birthRateSlider;
    
    RectangleShape statusRect{}; 
    
    RectangleShape selectionBackGround{};
    List<SelectionButton*> selectionButtons{};
    
	List<SatisBar*> satisfyBar{};

	List<float> scoreList ;

    void DrawNextDayButton();
    void DrawTime();
    void DrawMoney();
    void DrawSelection();  
    void DrawSatisfaction() const; 
    void DrawStatus() const; 
    void DrawBirthRate();

    void InitSelection();
	void InitSatisfaction();
    void InitBirthRate();
	SFMLController& sfml;

    static SelectionButton* InitSelectionButton(int& y, const std::string& str, Color color);

};

