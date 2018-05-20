#pragma once
#include "SFMLController.h"
#include "./ViewPortController.h"
#include "../Systems/Plot/PlotSystem.h"

/**
 * \brief Acts as the core of the game, initializing all systems, handles events, 
 *        and calls the corresponding methods on each loop
 */
class CoreController
{
    
    friend class ViewPortController;
public:
    static CoreController* Instance() {return instance;};
    SFMLController* const& SfmlController() const { return sfmlController; }
    ViewPortController* const& GetViewportController() const { return viewPortController; }
    PlotSystem* const& GetPlotSystem() const { return plotSystem;}

    // Properties
    bool IsRunning() const;
    
    // Constructors and Destructors
    CoreController();
    ~CoreController();
    
    // Exposed Methods
    void Start() const;
    void RenderEvents() const;
private:
    static CoreController* instance;
    SFMLController *sfmlController;
    ViewPortController *viewPortController;
    
    // TODO : move to seperate controller
    PlotSystem* plotSystem;

private:
    bool isRunning;
    
    void Update() const;
    void HandleEvents() const;
    void ClearRender() const;    
    void PresentRender() const;
};


