#pragma once
#include <climits>
#include "../Controllers/CoreController.h"

/**
 * \brief Clamp (limits) an input number to within the lower and upper bounds
 * \tparam T Type of number being clamps
 * \param input number to clamp
 * \param lower lower bound to clamp to
 * \param upper upper bound to clamp to
 * \return Clamped results of input
 */
template<typename T>
static T Clamp(T input, T lower = INT_MIN, T upper = INT_MAX)
{
    return input > upper ? upper : (input < lower ? lower : input);
}

/**
 * \brief Returns a random number between lower and upper bound
 * \param lower Lower bound of random generator
 * \param upper Upper bound of random generator
 * \return Random integer between lower and upper bound
 */
static int RandomInt(const int lower, const int upper)
{
    return CoreController::Instance()->RandomInt(lower, upper);
}

