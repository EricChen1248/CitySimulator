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
    friend void MultithreadGameUpdates();
public:
    static CoreController* Instance() {return instance;};
    static SFMLController* SfmlController() { return Instance()->sfmlController; }
    static ViewPortController* GetViewportController() { return Instance()->viewPortController; }
    static SystemController* GetSystemController() { return Instance()->systemController; }
    static FontController* GetFontController() { return Instance()->fontController; }
    static UIController* GetUIController() { return Instance()->uiController; }
    
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
    bool advanceDay{};
    
    void Update();
    // Common Functions
    void ClearRender() const;    
    void PresentRender() const;
    // Game Functions
    void GameInputEvents() const;
    void GameUpdateEvents() const;
    void GameRenderEvents() const;
    // Interday Functions
    void InterdayInputEvents();
    void InterdayRenderEvents() const;
};


