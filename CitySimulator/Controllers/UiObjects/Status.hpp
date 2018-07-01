#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../../Systems/SystemEnum.h"
#include "Button.h"

enum Selection
{
    NONE_SELECTED,
    SYSTEM,
    PLOT,
    ROAD
};

class Plot;

class Status
{
public:
    Status();
    ~Status();
    void Init(int x, int y);
    void Draw();
    static Selection Selection;
    static Plot* SelectedPlot;
    static System SelectedSystem;
private:
    void DrawChildren();
    void DrawSystem();
    void DrawPlot();

    bool Grow();
    bool Shrink();
    sf::Text title;
    RectangleShape rect{};
    sf::Text buttonText;
    Button button;
    
    sf::Text closeText;
    Button closeButton;

    const int height = 200;
    bool mousePressed{};
    int width{};
    int x{};
    int y{};
    int changeHeight = 0;
};

