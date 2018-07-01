#include "Status.hpp"
#include "../CoreController.h"

Selection Status::Selection = NONE_SELECTED;
Plot* Status::SelectedPlot = nullptr;
System Status::SelectedSystem = NONE;
    
Status::Status()
= default;


Status::~Status()
= default;

void Status::Init(const int x, const int y)
{
    this->x = x;
    this->y = y;
    width = float(WINDOW_WIDTH) / 2 - 255;
    
    rect.setPosition(x, y);
    rect.setFillColor(WHITE);
    rect.setOutlineColor(BLACK);
    rect.setOutlineThickness(2);
    rect.setSize(Vector2f(width, height));
    
    title.setFillColor(BLACK);
    title.setCharacterSize(20);
    title.setPosition(x + 20, y + 10);
    title.setFont(FontController::Monofur());
    
    buttonText.setFillColor(BLACK);
    buttonText.setCharacterSize(20);
    buttonText.setPosition(x + 20, y + height - 34);
    buttonText.setFont(FontController::Monofur());
    
    button = Button(Vector2f(width - 42, 28), Vector2f(x + 20, y + height - 34), WHITE, MOUSE_OVER_COLOR);
}

void Status::Draw()
{
    CoreController::SfmlController()->DrawShape(rect);
    switch (Selection)
    {
    case SYSTEM:
        DrawSystem();
        break;
    case PLOT: 
        DrawPlot();
        break;
    case ROAD: break;
    default: ;
    }
    
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        mousePressed = false;
    }
}

void Status::DrawSystem()
{
    title.setString(SYSTEM_NAMES[int(SelectedSystem)]);
    CoreController::SfmlController()->DrawString(title);
    
    if (SelectedPlot == nullptr) return;
    if (button.Draw())
    {
        if (!mousePressed)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                mousePressed = true;
            }
        }
        else
        {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                CoreController::GetSystemController()->GetSystem(SelectedSystem)->Register(SelectedPlot);            
                Selection = PLOT;
            }
        }
    }
    
    ChangeString(buttonText, "Build", x + float(width) / 2);
    CoreController::SfmlController()->DrawString(buttonText);
}

void Status::DrawPlot()
{
    if (SelectedPlot->GetPlotType() == nullptr) return;
    
    title.setString(SYSTEM_NAMES[int(SelectedPlot->GetPlotType()->SystemType)]);
    CoreController::SfmlController()->DrawString(title);
    if (button.Draw())
    {
        if (!mousePressed)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                mousePressed = true;
            }
        }
        else
        {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                CoreController::GetSystemController()->GetSystem(SelectedPlot->GetPlotType()->SystemType)->Destroy(SelectedPlot);            
                CoreController::GetSystemController()->Plots()->ClearSelections();
            }
        }
    }
    
    ChangeString(buttonText, "Destroy", x + float(width) / 2);
    CoreController::SfmlController()->DrawString(buttonText);
}

void Status::ChangeString(sf::Text& text, const std::string& str, const float center)
{
    text.setString(str);
    const sf::FloatRect textRect = text.getLocalBounds();
    text.setPosition(Vector2f(center - textRect.width / 2 ,text.getPosition().y));
}

