#pragma once
#include "SFMLController.h"
#include "./ViewPortController.h"
#include "SystemController.h"

/**
 * \brief Acts as the core of the game, initializing all systems, handles events, 
 *        and calls the corresponding methods on each loop
 */

class CoreController
{
    
    friend class ViewPortController;
public:
    static CoreController* Instance() {return instance;};
    SFMLController* SfmlController() const { return sfmlController; }
    ViewPortController* GetViewportController() const { return viewPortController; }
    SystemController* GetSystemController() const { return systemController; }
    const helper::Time& GetTime() const { return time; }

    // Properties
    bool IsRunning() const;
    
    // Constructors and Destructors
    CoreController();
    ~CoreController();
    
    // Exposed Methods
    void Start() const;
    void RenderEvents() const;
    static int RandomInt(int bottom, int top);
private:
    static CoreController* instance;
    SFMLController *sfmlController;
    ViewPortController *viewPortController;
    SystemController *systemController;

    helper::Time time;
    bool isRunning;
    
    void Update() const;
    void GameUpdateEvents(float deltaTime) const;
    void HandleEvents() const;
    void ClearRender() const;    
    void PresentRender() const;
};


