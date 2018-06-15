#include "Government.h"
#include "CoreController.h"


float Government::taxDollars = 0;
float Government::birthRate = 0.3;

int Government::NewChildren(const int adultCount)
{
    const int thresh = birthRate * 100;
    int birthCount = 0;
    for (int i = 0; i < adultCount; ++++i)
    {
        const int rand = CoreController::RandomInt(0, 100);
        if (rand < thresh)
        {
            ++birthCount;
        }
    }
    return birthCount;
}
