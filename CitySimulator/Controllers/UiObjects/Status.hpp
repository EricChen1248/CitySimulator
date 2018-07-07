#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Button.h"
#include "../../Helpers/Road.h"
#include "../../Systems/Systems.h"
#include "../../Systems/SystemEnum.h"

enum Selection
{
    NONE_SELECTED,
    SYSTEM,
    PLOT,
    ROAD
};


class Status
{
public:
    Status();
    ~Status();
    void Init(int x, int y);
    void Draw();
    bool InBound() const;
    static bool BuildMode() { return buildMode; }
    static void Build(Plot* plot);
    static Selection Selection;
    static Road* SelectedRoad;
    static Plot* SelectedPlot;
    static System SelectedSystem;
private:
    void DrawChildren();
    void ToggleBuildMode();
    void DrawSystem();
    void DrawDoubleButton(BaseSystem * system);
    void DrawSingleButton();
    void DrawPlot();
    void DrawRoad();

    bool Grow();
    bool Shrink();
    
    sf::Text title;
    sf::Text content;
    
    RectangleShape rect{};
    
    Button button;
    sf::Text buttonText;
    
    Button leftButton;
    sf::Text leftButtonText;
    
    Button rightButton;
    sf::Text rightButtonText;
    
    sf::Text closeText;
    Button closeButton;

    const int height = 250;
    int width{};
    int x{};
    int y{};
    int changeHeight = 0;
    
    static bool buildMode;
};

