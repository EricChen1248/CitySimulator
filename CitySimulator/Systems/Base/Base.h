#pragma once
#include <SFML/Graphics.hpp>
#include "../SystemEnum.h"
#include "../../Helpers/Constants.h"
class Plot;

/**
 * \brief Abstract class that is the base of all the system types
 */
class Base
{
public:
    System SystemType;

    const sf::Color& Color() const { return color; }
    Base(Plot* plot, const System system): SystemType(system)
    {
        this->plot = plot;
        color = BLACK;
        score = 0;
    }

    virtual ~Base() = default;
    virtual void EndDay() = 0;
    virtual int ReturnScore() { return score; };
    
protected:
    Plot* plot;
    sf::Color color;
    int score;
};

inline void Base::EndDay()
{
    
}

