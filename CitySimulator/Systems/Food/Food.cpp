#include "Food.h"

Food::Food(Plot* plot) : Base(plot, FOOD)
{
    color = sf::Color::Magenta;
}
