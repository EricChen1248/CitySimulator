#include "CustomExceptions.h"

inline CodingError::CodingError(char const* const message) noexcept : std::exception(message)
{
}

inline char const* CodingError::what() const
{
    return nullptr;
}
