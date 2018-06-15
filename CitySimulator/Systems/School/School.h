#pragma once
#include "../Base/Base.h"

class SchoolRule;

/**
 * \brief School Class that handles the food plots of our city
 */
class School : public Base
{
friend SchoolRule;

    public:
    School(Plot* plot);
    ~School() = default;
    void EndDay() override;
private:
    int cost;
    
    void Enter();
};

