#pragma once
#include <SFML/Graphics.hpp>

const float PI = 3.1415926f;
const float COS60 = 0.5f;
const float COS30 = 0.86602f;
const float SIN60 = 0.86602f;
const float SIN30 = 0.5f;


const sf::Color BLACK = sf::Color::Black;
const sf::Color WHITE = sf::Color::White;
const sf::Color BLUE = sf::Color::Blue;
const sf::Color DARK_GREY = sf::Color(100,100,100);
const sf::Color LIGHT_GREY = sf::Color(150,150,150);

const sf::Color EMPTY_PLOT_COLOR = sf::Color(200, 200, 200);
const sf::Color FOOD_COLOR = sf::Color::Magenta;
const sf::Color WORK_COLOR = sf::Color::Cyan;
const sf::Color BANK_COLOR = sf::Color::Green;
const sf::Color HOME_COLOR = sf::Color::Yellow;
const sf::Color STORE_COLOR = sf::Color::Red;
const sf::Color MOUSE_OVER_COLOR = sf::Color(220, 220, 220);
    
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;


const int CITIZEN_MAX_MONEY = 10000;
#ifdef _DEBUG
    const int LEFT = -15;
    const int RIGHT = 16;
#else
    const int LEFT = -20;
    const int RIGHT = 21;
#endif