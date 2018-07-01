#pragma once
#include <SFML/Graphics.hpp>

const float PI = 3.1415926f;
const float COS60 = 0.5f;
const float COS30 = 0.86602f;
const float SIN60 = 0.86602f;
const float SIN30 = 0.5f;


const sf::Color RED = sf::Color(255,0,0);
const sf::Color BLUE = sf::Color(0,0,255);
const sf::Color BLACK = sf::Color(0,0,0);
const sf::Color WHITE = sf::Color(255,255,255);
const sf::Color GREEN = sf::Color(0,255,0);
const sf::Color YELLOW = sf::Color(255,242,0);
const sf::Color DARK_GREY = sf::Color(100,100,100);
const sf::Color LIGHT_GREY = sf::Color(150,150,150);

const sf::Color EMPTY_PLOT_COLOR = sf::Color(200, 200, 200);
const sf::Color FOOD_COLOR = sf::Color::Magenta;
const sf::Color WORK_COLOR = sf::Color::Cyan;
const sf::Color BANK_COLOR = GREEN;
const sf::Color HOME_COLOR = YELLOW;
const sf::Color STORE_COLOR = RED;
const sf::Color SCHOOL_COLOR = RED;
const sf::Color HOSPITAL_COLOR = RED;
const sf::Color RIVER_COLOR = sf::Color(141, 250, 236);

const sf::Color MOUSE_OVER_COLOR = sf::Color(220, 220, 220);

const sf::Color UNSATISFIED_COLOR = RED;
const sf::Color SATISFIED_COLOR = YELLOW;
const sf::Color SUPER_SATIFIED_COLOR = GREEN;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

const int CITIZEN_MAX_MONEY = 10000;

// NONE,    FOOD,	WORK,	BANK,	HOME,	STORE, 	SCHOOL,    HOSPITAL
const std::string SYSTEM_NAMES[8] {"None", "Food", "Work", "Bank", "Home", "Store", "School", "Hospital"};
#ifdef _DEBUG
    const int LEFT = -15;
    const int RIGHT = 16;
#else
    const int LEFT = -20;
    const int RIGHT = 21;
#endif

