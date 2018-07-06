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
    void Left(float i = 1.f);
    void Right(float i = 1.f);
    void Up(float i = 1.f);
    void Down(float i = 1.f);
    
private:
    float scrollSize;
    sf::View gameView;
    sf::View uiView;
    
};

