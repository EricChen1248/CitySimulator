#pragma once
#include <exception>

class CodingError : public std::exception
{
public:
    CodingError(char const* const message) noexcept;
    ~CodingError() noexcept override;
    char const* what() const override;
};
