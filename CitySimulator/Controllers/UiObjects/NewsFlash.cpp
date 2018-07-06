#include "NewsFlash.hpp"
#include "../CoreController.h"
#include "../FontController.h"
#include "../SFMLController.h"
#include "../../Helpers/Constants.h"


NewsFlash::NewsFlash() : width(0), flash(false)
{
    text.setCharacterSize(120);
    text.setFillColor(RED);
    text.setFont(FontController::Monofur());
    text.setStyle(sf::Text::Bold);
    left = WINDOW_WIDTH;
}

NewsFlash::~NewsFlash()
= default;

void NewsFlash::Render()
{
    if (!flash) return;
    
    left -= 10;
    if (left + width <= 0)
    {
        flash = false;
        return;
    }
    text.setPosition(left, float(WINDOW_HEIGHT) / 2 - 160);
    CoreController::SfmlController()->DrawString(text);
}

void NewsFlash::Flash(const std::string& str)
{
    text.setString(str);
    left = WINDOW_WIDTH;
    width = text.getLocalBounds().width;
    flash = true;
}
