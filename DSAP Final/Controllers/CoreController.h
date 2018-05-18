#pragma once

class CoreController
{
public:
    // Properties
    bool IsRunning() const;
    
    // Constructors and Destructors
    CoreController();
    ~CoreController();
    
    // Exposed Methods
    void Update();
    void HandleEvents();
private:
    bool isRunning;
};


