#pragma once
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
    const sf::View& GameView() const { return gameView; }
    
    void HandleScroll(sf::Event& event);
    void UpdateGameView() const;
    void UpdateUIView() const;
    void Left();
    void Right();
    void Up();
    void Down();
    
private:
    float scrollSize;
    sf::View gameView;
    sf::View uiView;
    
};

