#pragma once
#include <SFML/Graphics.hpp>
#include "../SystemEnum.h"
class Plot;
class Base
{
public:
    System SystemType;

    const sf::Color& Color() const { return color; }
    Base(Plot* plot, const System system): SystemType(system)
    {
        this->plot = plot;
        color = sf::Color::Black;
    }

    virtual ~Base() = default;
    
protected:
    Plot* plot;
    sf::Color color;
};

