#pragma once
#include "SFMLController.h"
#include "./ViewPortController.h"
#include "SystemController.h"
#include "FontController.h"
#include "UIController.h"

/**
 * \brief Acts as the core of the game, initializing all systems, handles events, 
 *        and calls the corresponding methods on each loop
 */

class UIController;

using sf::Clock;
class CoreController
{
    
    friend class ViewPortController;
public:
    static CoreController* Instance() {return instance;};
    SFMLController* SfmlController() const { return sfmlController; }
    ViewPortController* GetViewportController() const { return viewPortController; }
    SystemController* GetSystemController() const { return systemController; }
    FontController* GetFontController() const { return fontController; }
    UIController* GetUIController() const { return uiController; }
    
    const helper::Time& GetTime() const { return time; }
    float GetDeltaTime() const { return deltaTime; }
    // Properties
    bool IsRunning() const;
    
    // Constructors and Destructors
    CoreController();
    ~CoreController();
    
    // Exposed Methods
    void Start();
    void RunDayLoop(Clock& clock);
    void GameRenderEvents() const;
    static int RandomInt(int bottom, int top);
private:
    static CoreController* instance;
    SFMLController *sfmlController;
    ViewPortController *viewPortController;
    SystemController *systemController;
    FontController *fontController;
    UIController *uiController;
    
    helper::Time time;
    float deltaTime{};
    bool isRunning;
    
    void Update();
    // Common Functions
    void ClearRender() const;    
    void PresentRender() const;
    // Game Functions
    void GameUpdateEvents() const;
    void GameInputEvents() const;
    // Interday Functions
    void InterdayInputEvents() const;
};


