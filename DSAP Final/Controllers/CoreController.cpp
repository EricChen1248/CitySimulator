#include "CoreController.h"
#include <iostream>

bool CoreController::IsRunning() const
{
    return isRunning;
}

CoreController::CoreController()
{
    isRunning = true;
};
CoreController::~CoreController() = default;

void CoreController::Update()
{
    std::cout << "I am game core";
}

void CoreController::HandleEvents()
{
    
}
