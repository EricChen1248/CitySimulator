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
    void DrawSystem();
    void DrawPlot();

    sf::Text title;
    RectangleShape rect{};
    sf::Text buttonText;
    Button button;

    const int height = 200;
    bool mousePressed{};
    int width{};
    int x{};
    int y{};
};

