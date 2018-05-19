#pragma once
#include "SFMLController.h"
#include "./MapController.h"
#include "../Systems/Plot/PlotSystem.h"
#include <SFML/Graphics.hpp>

class CoreController
{
    
    friend class MapController;
public:
    static CoreController* Instance() {return instance;};
    SFMLController* const& SfmlController() const { return sfmlController; }
    MapController* const& GetMapController() const { return mapController; }

    // Properties
    bool IsRunning() const;
    
    // Constructors and Destructors
    CoreController();
    ~CoreController();
    
    // Exposed Methods
    void Update();
    void Render(Drawable& shape) const;
private:
    static CoreController* instance;
    SFMLController *sfmlController;
    MapController *mapController;
    
    // TODO : move to seperate controller
    PlotSystem* plotSystem;
    
    bool isRunning;
    
    void HandleEvents();
    void ClearRender() const;    
    void PresentRender() const;
    
    
};


