#pragma once
#include "../SystemEnum.h"
#include "../../Controllers/CoreController.h"
#include "../../Controllers/SystemController.h"

class Plot;
/**
 * \brief Abstract class that is the base of all the system types
 */
class Base
{
public:
    const System SystemType;

    const sf::Color& Color() const { return color; }
    int Cost() const { return cost; }
    Base(Plot* plot, System system);

    virtual ~Base() = default;
    virtual void NewDay() { }
    virtual void EndDay() { }
    [[deprecated]]
    virtual int ReturnScore() { return 0; }
    
    virtual int Destroy();
    virtual std::string ContentString() { return ""; }
    
protected:
    int cost = 0;
    Plot* plot;
    sf::Color color;
    [[deprecated]]
    int score;
};
