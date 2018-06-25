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
    return CoreController::RandomInt(lower, upper);
}


/**
 * \brief Gets the larger of two values
 * \tparam T Type of value being compared
 * \param t1 First value being compared
 * \param t2 Second value being compared
 * \return the larger of the t1 and t2
 */
template<typename T>
static T Max(T t1, T t2)
{
    if (t1 > t2)
    {
        return t1;
    }
    return t2;
}


/**
 * \brief Gets the smalelr of two values
 * \tparam T Type of value being compared
 * \param t1 First value being compared
 * \param t2 Second value being compared
 * \return the smaller of the t1 and t2
 */
template<typename T>
static T Min(T t1, T t2)
{
    if (t1 < t2)
    {
        return t1;
    }
    return t2;
}

