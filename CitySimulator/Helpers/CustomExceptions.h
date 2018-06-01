#pragma once
#include <stdexcept>

/**
 * \brief Exception that should be used when the code somehow runs to somewhere that should have never happened
 *        i.e. the default case of an enum switch with no missing cases
 */
class CodingError : public std::logic_error
{
public:
    explicit CodingError(const std::string& message) : logic_error(message) {}
    explicit CodingError(const char* message) : logic_error(message) {}
    
    ~CodingError() noexcept override = default;
    
    char const* what() const override {return nullptr;};
};


/**
 * \brief Exception that should be used when a singleton/static class is initialized twice
 */
class DuplicateInitialization : public std::runtime_error
{
public:
    explicit DuplicateInitialization(const std::string& message) : runtime_error(message) {}
    explicit DuplicateInitialization(const char* message) : runtime_error(message) {}
    
    ~DuplicateInitialization() noexcept override = default;
    
    char const* what() const override {return nullptr;};
};