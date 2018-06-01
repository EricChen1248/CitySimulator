#pragma once
#include <stdexcept>

class CodingError : public std::logic_error
{
public:
    explicit CodingError(const std::string& message) : logic_error(message) {}
    explicit CodingError(const char* message) : logic_error(message) {}
    
    ~CodingError() noexcept override = default;
    
    char const* what() const override {return nullptr;};
};


class DuplicateInitialization : public std::runtime_error
{
public:
    explicit DuplicateInitialization(const std::string& message) : runtime_error(message) {}
    explicit DuplicateInitialization(const char* message) : runtime_error(message) {}
    
    ~DuplicateInitialization() noexcept override = default;
    
    char const* what() const override {return nullptr;};
};