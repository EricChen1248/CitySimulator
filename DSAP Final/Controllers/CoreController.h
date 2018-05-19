#pragma once
#include "SDLController.h"

class CoreController
{
public:
    static CoreController* Instance() {return instance;};
    // Properties
    bool IsRunning() const;
    
    // Constructors and Destructors
    CoreController();
    ~CoreController();
    
    // Exposed Methods
    void Update();
private:
    static CoreController* instance;
    SDLController sdlController;
    bool isRunning;
    
    void HandleEvents();
    void Render() const;
};


