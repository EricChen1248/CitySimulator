#pragma once
#include <exception>

class CodingError : public std::exception
{
public:
    CodingError(char const* const message) noexcept : std::exception(message) {};
    ~CodingError() noexcept override = default;
    char const* what() const override {return nullptr;};
};
