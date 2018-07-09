#pragma once
#include "../Base/Base.h"
#include "../Citizen/Citizen.h"
#include "../../Collections/List.h"

class Home : public Base
{
    friend HomeRule;
public:
    Home(Plot* plot);
    ~Home() = default;

    void Register(Citizen* citizen);
    void Unregister(Citizen* citizen);

    void EndDay() override;
    int Destroy() override;

    bool Full() const;
    Plot* GetPlot() const { return plot; };
    std::string ContentString() override;
private:
    //each home has it's own capacity
    int homeCapacity;
    List<Citizen*> residents;
    int NumOfFamily() const;
};

