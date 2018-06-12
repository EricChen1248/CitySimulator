#include "UIController.h"
#include "CoreController.h"
#include "../Helpers/Constants.h"


UIController::UIController()
{
    nextDay = Button(Vector2f(105, 32), Vector2f(WINDOW_WIDTH - 107, WINDOW_HEIGHT - 34), WHITE, MOUSE_OVER_COLOR);
    nextDayText.setFont(CoreController::Instance()->GetFontController()->Monofur());
    nextDayText.setFillColor(BLACK);
    nextDayText.setCharacterSize(24);
    nextDayText.setPosition(WINDOW_WIDTH - 103, WINDOW_HEIGHT - 33);
    nextDayText.setString("Next Day");
        
    
    timeText.setFont(CoreController::Instance()->GetFontController()->Monofur());
    timeText.setFillColor(BLACK);
    timeText.setCharacterSize(24);
    timeText.setPosition(5, 2);
    
    timeRect.setSize(sf::Vector2f(70, 32));
    timeRect.setPosition(1,1);
    timeRect.setFillColor(WHITE);
    timeRect.setOutlineColor(BLACK);
    timeRect.setOutlineThickness(2);
}




UIController::~UIController() = default;

/**
 * \brief Renders UI
 */
void UIController::RenderUI()
{
    Time();
}

void UIController::RenderInterDayUI()
{
    NextDayButton();    
}

void UIController::NextDayButton()
{
    nextDay.Draw();
    CoreController::Instance()->SfmlController()->DrawString(nextDayText);
}

/**
 * \brief Game Clock 
 */
void UIController::Time()
{
    timeText.setString(CoreController::Instance()->GetTime().ToShortString());
    CoreController::Instance()->SfmlController()->DrawRect(timeRect, true);
    CoreController::Instance()->SfmlController()->DrawString(timeText);
}
