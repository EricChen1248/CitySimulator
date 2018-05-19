#pragma once
#include "SFMLController.h"
#include "./TextureController.h"
#include <SFML/Graphics.hpp>

class CoreController
{
    
    friend class TextureController;
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
    SFMLController *sfmlController;
    TextureController *textureController;
    bool isRunning;
    
    void HandleEvents();
    void ClearRender() const;    
    void Render(Drawable& shape) const;
    void PresentRender() const;
};


