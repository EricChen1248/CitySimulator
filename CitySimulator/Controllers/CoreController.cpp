#include "CoreController.h"
#include "ViewPortController.h"
#include <iostream>
#include "../Helpers/PathFinder/PathFinder.h"
#include "../Helpers/Logger.h"

CoreController *CoreController::instance;

using sf::Event;
using sf::Window;
using sf::Keyboard;

bool CoreController::IsRunning() const
{
    return isRunning && sfmlController->IsRunning();
}

CoreController::CoreController()
{
    instance = this;
    isRunning = true;
    sfmlController = new SFMLController;
    viewPortController = new ViewPortController;
    systemController = new SystemController;
    fontController = new FontController;
    uiController = new UIController;
    
    systemController->Initialize();
    PathFinder::Initialize();
    srand(static_cast<unsigned>(std::time(nullptr)));
};
CoreController::~CoreController()
{
    delete sfmlController;
    delete viewPortController;
    delete systemController;
    delete fontController;
    delete uiController;
    
};

void CoreController::Start()
{
    Update();
}

void MultithreadGameUpdates()
{
    CoreController::Instance()->GameUpdateEvents();
}
/**
 * \brief Game loop of each day
 * \param clock Reference to game clock
 */
void CoreController::RunDayLoop(Clock& clock)
{
#ifdef _DEBUG
        // HACK : set to true to skip to day end
        if (false)
        {
            time.IncreaseTime(24);
        }
#endif
    int day = 0;
    int count = 0;
    while(true)
    {
        float lastTime = clock.getElapsedTime().asSeconds();
        float lastPrint = lastTime;
        ++day;
        while(IsRunning() && !time.EndDay())
        {
            const float currentTime = clock.getElapsedTime().asSeconds();
            const float fps = 1.f / (currentTime - lastTime);
            if (currentTime - lastPrint > 0.2)
            {
                std::cout << fps << std::endl;
                lastPrint = currentTime;
            }
                        
            // DeltaTime 0.1 = 1/60 real seconds = 0.1 minute in game
            deltaTime = (currentTime - lastTime);
            time.IncreaseTime(deltaTime);
            lastTime = currentTime;
            
            GameInputEvents();
            
#ifdef MULTITHREAD      
            // Multithreaded needs some warm up ( I think it's because pathfinder's queue needs to get up to size?)
            if (count < 60)
            {
                GameUpdateEvents();
                GameRenderEvents();
                ++count;
            }
            else
            {
                sf::Thread thread(MultithreadGameUpdates);
                thread.launch();
                GameRenderEvents();
                thread.wait();
            }
#else
            GameUpdateEvents();
            GameRenderEvents();
#endif
            
            PresentRender();
            viewPortController->ResetMod();
        }
        advanceDay = false;
        Logger::Log("End of day " + std::to_string(day));
        while(!advanceDay)
        {
            InterdayInputEvents();
            InterdayRenderEvents();       
            PresentRender();
            viewPortController->ResetMod();
        }
        time.ResetDay();
        systemController->AdvanceDay();
    }
}

#pragma region Common Functions
/**
 * \brief Core loop of the game
 */
void CoreController::Update()
{
    Clock clock;
    RunDayLoop(clock);
    auto systems = systemController->GetSystems();
    for (auto && system : systems)
    {
        std:: cout << system->GetScore();
    }
    
    char a;
    std::cin >> a;
}

/**
 * \brief Update the render buffer
 */
void CoreController::PresentRender() const
{
    sfmlController->UpdateWindow();
}

/**
 * \brief Calls on SFML controller to clear the screen
 */
void CoreController::ClearRender() const
{
    sfmlController->ClearRender();
}

#pragma endregion

#pragma region Game Functions

/**
 * \brief Handles update event of games
 */
void CoreController::GameUpdateEvents() const
{
    systemController->Update();
}

/**
 * \brief Handles SFML events
 */
void CoreController::GameInputEvents()
{
    Window* window = sfmlController->Window();
    if (!window->hasFocus()) return;
    Event event{};
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
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        viewPortController->Right();
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        viewPortController->Left();
    }
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        viewPortController->Down();
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        viewPortController->Up();
    }
}


/**
 * \brief Calls the different render events
 */
void CoreController::GameRenderEvents() const
{
    ClearRender();
    viewPortController->UpdateGameView();
    systemController->Render();
    viewPortController->UpdateUIView();
    uiController -> RenderUI();
}

#pragma endregion 

#pragma region Interday Functions


void CoreController::InterdayInputEvents()
{
    Window* window = sfmlController->Window();
    if (!window->hasFocus()) return;
    Event event{};
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
        case Event::MouseButtonPressed: 
        case Event::MouseButtonReleased: break;
        case Event::MouseMoved: break;
        case Event::MouseEntered: break;
        case Event::MouseLeft: break;
        default: ;
        }        
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        viewPortController->Right();
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        viewPortController->Left();
    }
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        viewPortController->Down();
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        viewPortController->Up();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (uiController->NextDayButtonHover())
        {
           advanceDay = true;
        }
    }

}

void CoreController::InterdayRenderEvents() const
{
    ClearRender();
    viewPortController->UpdateGameView();
    systemController->RenderInterday();
    viewPortController->UpdateUIView();
    uiController -> RenderInterDayUI();
}
#pragma endregion

#pragma region Helper Functions

/**
 * \brief Generates a psuedorandom number with given ranges
 * \param bottom Lower bound of random number set
 * \param top Upper bound of random number set
 * \return Random number between lower and upper bound
 */
int CoreController::RandomInt(const int bottom, const int top)
{
    return rand() % (top - bottom) + bottom;
}

#pragma endregion 

