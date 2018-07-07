#pragma once
#include <SFML/Window/Event.hpp>

class MouseController
{
public:
    MouseController();
    ~MouseController();
    static void Reset();
    static bool IsClicked();
    static void Unclick(sf::Event& event);
private:
    static bool clicked;
};

