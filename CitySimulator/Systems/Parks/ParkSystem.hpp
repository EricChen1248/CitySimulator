#pragma once
#include "../Base/BaseSystem.h"

class ParkSystem : public BaseSystem
{
public:
    ParkSystem();
    ~ParkSystem();
    void Update() override;
    inline int Register(Plot* plot) override;
    inline void EndDay() override;
    int Cost() const override;
    float GetSatisfaction() const override;
    void TooFar(const Coordinate& coords);

    static const int CLOSE_ENUF;
private:
    List<Coordinate> tooFarList;
};

