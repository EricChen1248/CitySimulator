#include "UIController.h"
#include "CoreController.h"
#include "../Helpers/Constants.h"


UIController::UIController()
{
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
