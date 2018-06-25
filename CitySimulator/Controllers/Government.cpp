#include "Government.h"
#include "../Helpers/HelperFunctions.h"


float Government::taxDollars = 0.f;
float Government::birthRate = 0.3f;

int Government::NewChildren(const int adultCount)
{
    const int thresh = static_cast<int>(birthRate * 100);
    int birthCount = 0;
    for (int i = 0; i < adultCount; ++++i)
    {
        const int rand = RandomInt(0, 100);
        if (rand < thresh)
        {
            ++birthCount;
        }
    }
    return birthCount;
}
