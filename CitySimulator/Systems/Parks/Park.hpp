#pragma once
#include "../Base/Base.h"

class Park : public Base
{
    friend class ParkSystem;
public:
    Park(Plot* plot);
    ~Park();
    
    void Enter() override;
    void NewDay() override;
    std::string ContentString() override;
private:
    int visitors = 0;
};

