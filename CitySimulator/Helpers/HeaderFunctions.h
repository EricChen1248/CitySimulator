#pragma once
template<typename T>
static T Clamp(T input, T lower, T upper)
{
    return input > upper ? upper : (input < lower ? lower : input);
}

static int RandomInt(const int lower, const int upper)
{
    return CoreController::Instance()->RandomInt(lower, upper);
}