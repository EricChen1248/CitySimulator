#include "UIController.h"
#include "CoreController.h"

#include "UiObjects/Status.hpp"
#include "UiObjects/SatisBar.h"
#include "UiObjects/SelectionButton.h"

#include "../Helpers/Constants.h"
#include "../Helpers/Government.h"
#include "../Helpers/HelperFunctions.h"

#include "../Systems/Base/BaseSystem.h"
#include "../Systems/Plot/PlotSystem.h"
#include "MouseController.h"

UIController::UIController() : sfml(*CoreController::SfmlController()) {}

UIController::~UIController()
{
    selectionButtons.Dispose();
}

void UIController::Initialize()
{
    nextDay = Button(Vector2f(105, 32), Vector2f(WINDOW_WIDTH - 107, WINDOW_HEIGHT - 34), WHITE, MOUSE_OVER_COLOR);
    nextDayText.setFont(FontController::Monofur());
    nextDayText.setFillColor(BLACK);
    nextDayText.setCharacterSize(24);
    nextDayText.setPosition(WINDOW_WIDTH - 103, WINDOW_HEIGHT - 33);
    nextDayText.setString("Next Day");

    timeText.setFont(FontController::Monofur());
    timeText.setFillColor(BLACK);
    timeText.setCharacterSize(24);
    timeText.setPosition(WINDOW_WIDTH - 88, WINDOW_HEIGHT - 33);

    timeRect.setSize(Vector2f(105, 32));
    timeRect.setPosition(WINDOW_WIDTH - 107, WINDOW_HEIGHT - 34);
    timeRect.setFillColor(WHITE);
    timeRect.setOutlineColor(BLACK);
    timeRect.setOutlineThickness(2);

    moneyText.setFont(FontController::Monofur());
    moneyText.setFillColor(BLACK);
    moneyText.setCharacterSize(24);

    moneyRect.setSize(Vector2f(200, 32));
    moneyRect.setPosition(static_cast<float>(WINDOW_WIDTH) / 2 - 100, 2);
    moneyRect.setFillColor(WHITE);
    moneyRect.setOutlineColor(BLACK);
    moneyRect.setOutlineThickness(2);

    status.Init(2, 40);
    InitSelection();
    InitSatisfaction();
    InitBirthRate();
}


/**
 * \brief Renders UI
 */
void UIController::RenderUI()
{
    DrawTime();
    DrawMoney();
    DrawSelection();
    DrawSatisfaction();
    DrawBirthRate();
    Status::Selection = NONE_SELECTED;
    DrawStatus();
    flash.Render();
}

void UIController::RenderInterDayUI()
{
    DrawNextDayButton();
    DrawMoney();
    DrawSelection();
    DrawSatisfaction();
    DrawBirthRate();
    DrawStatus();
}

void UIController::Flash(const std::string& str)
{
    flash.Flash(str);
}


bool UIController::IsOverUI() const
{
    const auto window = CoreController::SfmlController()->Window();
    const auto mousePos = sf::Mouse::getPosition(*window);
    const float x = float(mousePos.x), y = float(mousePos.y);
    if (timeRect.getGlobalBounds().contains(x, y)) return true;
    if (moneyRect.getGlobalBounds().contains(x, y)) return true;
    if (selectionBackGround.getGlobalBounds().contains(x, y)) return true;
    if (nextDay.IsInBounds()) return true;
    if (birthRateSlider.InBound()) return true;
    return false;    
}

void UIController::InitSelection()
{
    selectionBackGround.setSize(Vector2f(151, 383));
    selectionBackGround.setPosition(WINDOW_WIDTH - 153, 2);
    selectionBackGround.setFillColor(WHITE);
    selectionBackGround.setOutlineColor(BLACK);
    selectionBackGround.setOutlineThickness(2);

    int y = 2;

    // NONE,    FOOD,	WORK,	BANK,	HOME,	STORE, 	SCHOOL,    HOSPITAL
    const int systemCount = 7;
    //CoreController::Instance()->GetSystemController()->GetNumOfSystem();
    std::string strings[systemCount]{"Food", "Work", "Bank", "Home", "Store", "School", "Hospital"};
    Color colors[systemCount]{
        FOOD_COLOR, WORK_COLOR, BANK_COLOR, HOME_COLOR, STORE_COLOR, SCHOOL_COLOR, HOSPITAL_COLOR
    };
    for (int i = 0; i < systemCount; ++i)
    {
        selectionButtons.InsertLast(InitSelectionButton(y, strings[i], colors[i]));
    }
}

void UIController::InitSatisfaction()
{
    const int systemCount = 7;
    for (int i = 1; i <= systemCount; i++)
    {
        SatisBar* tempPtr = new SatisBar(static_cast<System>(i));
        satisfyBar.InsertLast(tempPtr);
    }
    return;
}

void UIController::InitBirthRate()
{
    birthRateSlider = Slider(Vector2f(2, 2), Vector2f(250, 36));
}

SelectionButton* UIController::InitSelectionButton(int& y, const std::string& str, const Color color)
{
    const auto button = new SelectionButton(Vector2f(150.f, 32.f), Vector2f(WINDOW_WIDTH - 152.f, float(y)), WHITE,
                                            MOUSE_OVER_COLOR, str, y, color);
    y += 55;
    return button;
}

void UIController::DrawStatus()
{
    for (int i = 0; i < selectionButtons.Count(); ++i)
    {
        if (selectionButtons[i]->IsInBounds())
        {
            if (MouseController::IsClicked())
            {
                PlotSystem::DeselectPlotsAndRoads();
                Status::Selection = SYSTEM;
                Status::SelectedSystem = System(i + 1);
            }
        }
    }
    status.Draw();
}

void UIController::DrawBirthRate()
{
    birthRateSlider.Render();
    Government::ChangeBirthRate(float(birthRateSlider.Value()) / 100);
}

void UIController::DrawSelection()
{
    sfml.DrawShape(selectionBackGround);
    for (auto&& selectionButton : selectionButtons)
    {
        selectionButton->Draw(sfml);
    }
}

void UIController::DrawSatisfaction()
{
    scoreList.Clear();
    const auto systems = CoreController::GetSystemController();
    for (auto system : systems->GetSystems())
    {
        scoreList.InsertLast(system->GetSatisfaction());
    }
    
    if (scoreList.Count() > 0)
    {
        for (int i = 0; i < satisfyBar.Count(); i++)
        {
            auto tempPtr = satisfyBar[i];
            tempPtr->Draw(scoreList[i], sfml);
        }
    }
}

/**
 * \brief Game Clock 
 */
void UIController::DrawTime()
{
    timeText.setString(CoreController::Instance()->GetTime().ToShortString());
    sfml.DrawShape(timeRect);
    sfml.DrawString(timeText);
}

/**
 * \brief Draws the player money
 */
void UIController::DrawMoney()
{
    CenterString(moneyText, "$" + std::to_string(static_cast<int>(Government::TaxDollars())), float(WINDOW_WIDTH) / 2);
    sfml.DrawShape(moneyRect);
    sfml.DrawString(moneyText);
}

/**
 * \brief Button to advance to next day
 */
void UIController::DrawNextDayButton()
{
    nextDay.Draw();
    sfml.DrawString(nextDayText);
}
