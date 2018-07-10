#include "Park.hpp"
#include "../../Helpers/Constants.h"

Park::Park(Plot* plot) : Base(plot, PARK)
{
    cost = 1000;
    color = PARK_COLOR;
}

Park::~Park()
= default;

std::string Park::ContentString()
{
    std::stringstream ss;
    ss << "Citizens built this" << std::endl << "to congregate when" << std::endl << "they have nothing to do" << std::endl << std::endl ;
    ss << "Today's Visitors: " << visitors;
    
    return ss.str();
}

void Park::Enter()
{
    ++visitors;
}

void Park::NewDay()
{
    visitors = 0;
}
