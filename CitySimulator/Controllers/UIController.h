#pragma once
#include "SFMLController.h"
#include "UiObjects/Slider.h"
#include "UiObjects/Button.h"
#include "UiObjects/Status.hpp"
#include "../Collections/List.h"
#include "UiObjects/NewsFlash.hpp"

struct SatisBar;
struct SelectionButton;

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
    void Flash(const std::string& str);
    bool NextDayButtonHover() const { return nextDay.IsInBounds(); };
    
    bool IsOverUI() const;
    const RectangleShape& SelectionBack() const { return selectionBackGround;}
    List<float>& GetScoreList() { return scoreList; };
private:
    sf::Text timeText{};
    RectangleShape timeRect{};

    sf::Text moneyText{};
    RectangleShape moneyRect{};

    Button nextDay;
    sf::Text nextDayText{};

    Status status{};
    Slider birthRateSlider;
    sf::Text birthText{};
    RectangleShape birthRect{};
    
    RectangleShape topRect{};
    sf::Text citizenText{};
    sf::Text citizenCountText{};
    sf::Text familyText{};
    sf::Text familyCountText{};
    
    
    NewsFlash flash{};
    
    RectangleShape selectionBackGround{};
    List<SelectionButton*> selectionButtons{};

    List<SatisBar*> satisfyBar{};

    List<float> scoreList;

    void DrawNextDayButton();
    void DrawTime();
    void DrawTop();
    void DrawSelection();
    void DrawSatisfaction();
    void DrawStatus();
    void DrawBirthRate();

    void InitSelection();
    void InitSatisfaction();
    void InitBirthRate();
    void InitTop();
    SFMLController& sfml;

    static SelectionButton* InitSelectionButton(int& y, const std::string& str, Color color);
};

