#pragma once
#include "../Helpers/Coordinate.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>

/**
 * \brief Handles the viewport of the screen
 */
class ViewPortController
{
public:
    ViewPortController();
    ~ViewPortController();
    const float& Modifier() const { return modifier; }
    const sf::View& GameView() const { return gameView; }
    
    ScreenCoordinate ToDrawCoord(ScreenCoordinate sCoords) const;
    void HandleScroll(sf::Event& event);
    void UpdateGameView();
    void UpdateUIView() const;
    void ResetMod();
    void Left();
    void Right();
    void Up();
    void Down();

    int ViewX() const { return viewX; }
    int ViewY() const { return viewY; }
private:
    int viewX;
    int viewY;
    float scrollSize;
    float modifier;
    sf::View gameView;
    sf::View uiView;
    
};

