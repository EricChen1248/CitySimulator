#include "UIController.h"
#include "CoreController.h"


UIController::UIController()
{
    timeText.setFont(CoreController::Instance()->GetFontController()->Monofur());
    timeText.setFillColor(Color::Black);
    timeText.setCharacterSize(24);
    timeText.setPosition(5, 2);
    
    timeRect.setSize(Vector2f(70, 32));
    timeRect.setPosition(1,1);
    timeRect.setFillColor(Color::White);
    timeRect.setOutlineColor(Color::Black);
    timeRect.setOutlineThickness(2);
}




UIController::~UIController()
= default;

/**
 * \brief Renders UI
 */
void UIController::RenderUI()
{
    Time();
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
