#pragma once
#include <SFML/Graphics.hpp>

const float PI = 3.1415926f;
const float COS60 = 0.5f;
const float COS30 = 0.86602f;
const float SIN60 = 0.86602f;
const float SIN30 = 0.5f;

const sf::Color BACKGROUND = sf::Color(235,235,235);

const sf::Color RED = sf::Color(255,0,0);
const sf::Color BLUE = sf::Color(0,0,255);
const sf::Color BLACK = sf::Color(0,0,0);
const sf::Color WHITE = sf::Color(255,255,255);
const sf::Color GREEN = sf::Color(0,255,0);
const sf::Color YELLOW = sf::Color(255,242,0);
const sf::Color DARK_GREY = sf::Color(100,100,100);
const sf::Color LIGHT_GREY = sf::Color(150,150,150);
const sf::Color TRANSPARENT = sf::Color(0,0,0,0);

const sf::Color EMPTY_PLOT_COLOR = sf::Color(200, 200, 200);
const sf::Color FOOD_COLOR = sf::Color::Magenta;
const sf::Color WORK_COLOR = sf::Color::Cyan;
const sf::Color BANK_COLOR = sf::Color(241,137,10);
const sf::Color HOME_COLOR = sf::Color(128,64,0);
const sf::Color STORE_COLOR = RED;
const sf::Color SCHOOL_COLOR = sf::Color(64,128,128);
const sf::Color HOSPITAL_COLOR = GREEN;
const sf::Color PARK_COLOR = sf::Color(0,121,0);
const sf::Color RIVER_COLOR = sf::Color(141, 250, 236);
const sf::Color RIVER_COLOR_2 = sf::Color(62, 244, 240);

const sf::Color BASE_ROAD_COLOR = sf::Color(230, 230, 230);
const sf::Color MOUSE_OVER_COLOR = sf::Color(220, 220, 220);

const sf::Color SATISFIED_COLOR = YELLOW;
const sf::Color SUPER_SATIFIED_COLOR = GREEN;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
//Citizen's constant
const int CITIZEN_MIN_MONEY = 350;
const int CITIZEN_MAX_MONEY = 1500;
const int WORKING_AGE = 18;
const int RETIREMENT_AGE = 45;
const int HOSPITALIZED_AGE = 54;
// NONE,    FOOD,	WORK,	BANK,	HOME,	STORE, 	SCHOOL,    HOSPITAL
const std::string SYSTEM_NAMES[9] {"None", "Food", "Work", "Bank", "Home", "Store", "School", "Hospital", "Park"};
#ifdef _DEBUG
    const int LEFT = -15;
    const int RIGHT = 16;
#else
    const int LEFT = -20;
    const int RIGHT = 21;
#endif

