#include "CoreController.h"
#include "ViewPortController.h"
#include <iostream>
#include "../Systems/Citizen/Citizen.h"

CoreController *CoreController::instance;

bool CoreController::IsRunning() const
{
    return isRunning && sfmlController->IsRunning();
}

CoreController::CoreController()
{
    instance = this;
    isRunning = true;
    sfmlController = new SFMLController();
    viewPortController = new ViewPortController();
    plotSystem = new PlotSystem();
    
    srand(static_cast<unsigned>(time(nullptr)));
};
CoreController::~CoreController() = default;

void CoreController::Start() const
{
    Update();
}

/**
 * \brief Core loop of the game
 */
void CoreController::Update() const
{
    int citCount = 5000;
    
#ifdef _DEBUG
    citCount = 1000;
#endif
    
    Citizen* citizens = new Citizen[citCount];
    Clock clock;
    float lastTime = 0;
    float lastPrint = 0;
    while(IsRunning())
    {
        const float currentTime = clock.getElapsedTime().asSeconds();
        const float fps = 1.f / (currentTime - lastTime);
        if (currentTime - lastPrint > 0.2)
        {
            std::cout << fps << std::endl;
            lastPrint = currentTime;
        }
        lastTime = currentTime;
        const float deltaTime = 60 / fps * 0.01f;
        HandleEvents();
        ClearRender();

        for (int i = 0; i < citCount; ++i)
        {
            citizens[i].Update(deltaTime);
            auto & shape = citizens[i].GetShape();
            SfmlController()->DrawCircle(shape);
        }
        
        RenderEvents();
        
        PresentRender();
        viewPortController->ResetMod();
    }
    delete [] citizens;
}

/**
 * \brief Handles SFML events
 */
void CoreController::HandleEvents() const
{
    Event event{};
    Window* window = sfmlController->Window();
    while (window->pollEvent(event))
    {
        // "close requested" event: we close the window
        switch (event.type)
        {
        case Event::Closed:
            window->close();
            break;
        case Event::Resized: break;
        case Event::TextEntered: break;
        case Event::MouseWheelMoved: break;
        case Event::MouseWheelScrolled:
            viewPortController->HandleScroll(event);
            break;
        case Event::MouseButtonPressed: break;
        case Event::MouseButtonReleased: break;
        case Event::MouseMoved: break;
        case Event::MouseEntered: break;
        case Event::MouseLeft: break;
        default: ;
        }        
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::A))
    {
        viewPortController->Right();
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::D))
    {
        viewPortController->Left();
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::W))
    {
        viewPortController->Down();
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::S))
    {
        viewPortController->Up();
    }

}

/**
 * \brief Calls on SFML controller to clear the screen
 */
void CoreController::ClearRender() const
{
    sfmlController->ClearRender();
}

/**
 * \brief Calls the different render events
 */
void CoreController::RenderEvents() const
{
    plotSystem->Render();
}

/**
 * \brief Update the render buffer
 */
void CoreController::PresentRender() const
{
    sfmlController->UpdateWindow();
}

