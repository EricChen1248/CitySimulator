#include "Food.h"
#include "../../Controllers/CoreController.h"

Food::Food(Plot* plot) : Base(plot, FOOD)
{
    cost = CoreController::RandomInt(50, 100);
    earnings = 0;
    color = sf::Color::Magenta;
}

/**
 * \brief Reset's Food Plot (earnings to 0)
 */
void Food::Reset()
{
    earnings = 0;
}


/**
 * \brief New entry ( +earnings )
 */
void Food::Enter()
{
    earnings += cost;
}
