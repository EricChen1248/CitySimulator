#pragma once
#include <climits>
#include "../Controllers/CoreController.h"

template<typename T>
static T Clamp(T input, T lower = INT_MIN, T upper = INT_MAX)
{
    return input > upper ? upper : (input < lower ? lower : input);
}

static int RandomInt(const int lower, const int upper)
{
    return CoreController::Instance()->RandomInt(lower, upper);
}

