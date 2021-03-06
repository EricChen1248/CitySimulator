#include <iostream>
#include "UIController.h"
#include "CoreController.h"
#include "SFMLController.h"
#include "FontController.h"
#include "MouseController.h"
#include "SystemController.h"
#include "ViewPortController.h"
#include "DisasterController.h"
#include "../Helpers/Logger.h"
#include "../Helpers/FeatureFlags.h"
#include "../Helpers/PathFinder/PathFinder.hpp"
#include "../Helpers/Government.h"
CoreController* CoreController::instance = nullptr;

using sf::Event;
using sf::Window;
using sf::Keyboard;
void MultithreadGameUpdates();

CoreController::CoreController() : time(0, 0)
{
    srand(static_cast<unsigned>(std::time(nullptr)));
    instance = this;
    isRunning = true;
    PathFinder::Initialize();
    sfmlController = new SFMLController;
    viewPortController = new ViewPortController;
    systemController = new SystemController;
    fontController = new FontController;
    uiController = new UIController;
    disasterController = new DisasterController;

    systemController->Initialize();
    uiController->Initialize();
    PathFinder::RemapQuadrants();
    
#if LOTS_OF_MONEY
    Government::AddTax(1000000);
#endif
    
};

CoreController::~CoreController()
{
    delete sfmlController;
    delete viewPortController;
    delete systemController;
    delete fontController;
    delete uiController;
};

/**
 * \brief Starts the game and kicks off all functions
 */
void CoreController::Start()
{
    Clock clock;

#if SKIP_DAY
    time.IncreaseTime(24);
#endif

    systemController->AdvanceDay();
    while (true)
    {
        ++day;
        RunDayLoop(clock);
        Logger::Log("End of day " + std::to_string(day));
        EndDayLoop();
    }
}

/**
 * \brief Game loop of each day
 * \param clock Reference to game clock
 */
void CoreController::RunDayLoop(Clock& clock)
{
    int count = 0;
    float lastTime = clock.getElapsedTime().asSeconds();
    float lastPrint = lastTime;
    while (IsRunning() && !time.EndDay())
    {
        const float currentTime = clock.getElapsedTime().asSeconds();
        const float fps = 1.f / (currentTime - lastTime);
        if (currentTime - lastPrint > 0.2)
        {
            std::cout << fps << std::endl;
            lastPrint = currentTime;
        }

        // DeltaTime 0.017 = 1/60 real seconds = 1 minute in game
        deltaTime = (currentTime - lastTime);
#if SUPER_SPEED
        deltaTime *= 3;
#endif
        time.IncreaseTime(deltaTime);
        lastTime = currentTime;

        GameInputEvents();

        // Multithreaded needs some warm up ( I think it's because pathfinder's queue needs to get up to size? )
        if (count < 60)
        {
            GameUpdateEvents();
            GameRenderEvents();
            ++count;
        }
        else
        {
            // Launch update events in a separate thread
            sf::Thread thread(MultithreadGameUpdates);

            thread.launch();
            // Run render events on main thread
            GameRenderEvents();
            // Wait for update events to finish (most of the time  it finishes first)
            thread.wait();
        }
	    MouseController::Reset();
        PresentRender();
    }
}

void CoreController::EndDayLoop()
{
    advanceDay = false;
    systemController->ResetDay();
    while (!advanceDay)
    {
        InterdayInputEvents();
        InterdayRenderEvents();
        PresentRender();
	    MouseController::Reset();
    }
    time.ResetDay();
    systemController->AdvanceDay();
}


#pragma region Common Functions

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
    disasterController->Update();
}

/**
 * \brief Handles SFML events
 */
void CoreController::GameInputEvents() const
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
        case Event::MouseButtonReleased: 
            MouseController::Unclick(event);
            break;
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
    viewPortController->UpdateGameView();
    ClearRender();
    systemController->Render();
    viewPortController->UpdateUIView();
    uiController->RenderUI();
}

#pragma endregion

#pragma region Interday Functions

/**
 * \brief Handle input events during interday
 */
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
        case Event::MouseButtonPressed: break;
        case Event::MouseButtonReleased: 
            MouseController::Unclick(event);
            break;
        case Event::MouseMoved: break;
        case Event::MouseEntered: break;
        case Event::MouseLeft: break;
        default:;
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
    if (MouseController::IsClicked())
    {
        if (uiController->NextDayButtonHover())
        {
            advanceDay = true;
        }
    }
}

/**
 * \brief Handles the rendering events during interday
 */
void CoreController::InterdayRenderEvents() const
{
    viewPortController->UpdateGameView();
    ClearRender();
    systemController->RenderInterday();
    viewPortController->UpdateUIView();
    uiController->RenderInterDayUI();
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

bool CoreController::IsRunning() const
{
    return isRunning && sfmlController->IsRunning();
}

/**
 * \brief Function used in multithreaded version
 */
void MultithreadGameUpdates()
{
    CoreController::Instance()->GameUpdateEvents();
}

#pragma endregion

