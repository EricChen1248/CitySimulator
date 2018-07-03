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
    virtual void NewDay() { }
    virtual void EndDay() { }
    virtual int ReturnScore() { return score; }
    // TODO : Add Destroy behaviour
    virtual int Destroy() { return 0; }
    virtual std::string ContentString() { return ""; }
    
protected:
    Plot* plot;
    sf::Color color;
    int score;
};
