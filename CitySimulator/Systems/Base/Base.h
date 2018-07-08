#pragma once
#include "../SystemEnum.h"
#include "../../Helpers/Constants.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SystemController.h"
class Plot;

/**
 * \brief Abstract class that is the base of all the system types
 */
class Base
{
public:
    System SystemType;

    const sf::Color& Color() const { return color; }
    int Cost() const { return cost; }
    Base(Plot* plot, const System system);

    virtual ~Base() = default;
    virtual void NewDay() { }
    virtual void EndDay() { }
    [[deprecated]]
    virtual int ReturnScore() { return score; }
    
    // TODO : Add Destroy behaviour
    virtual int Destroy();
    virtual std::string ContentString() { return ""; }
    
protected:
    int cost = 0;
    Plot* plot;
    sf::Color color;
    int score;
};
