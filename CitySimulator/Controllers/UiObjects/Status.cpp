#include "Status.hpp"
#include "../CoreController.h"
#include "../../Helpers/HelperFunctions.h"

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
    rect.setSize(Vector2f(width, 0));

    title.setFillColor(BLACK);
    title.setCharacterSize(20);
    title.setPosition(x + 20, y + 10);
    title.setFont(FontController::Monofur());

    buttonText.setFillColor(BLACK);
    buttonText.setCharacterSize(20);
    buttonText.setPosition(x + 20, y + height - 34);
    buttonText.setFont(FontController::Monofur());

    button = Button(Vector2f(width - 42, 28), Vector2f(x + 20, y + height - 34), WHITE, MOUSE_OVER_COLOR);
    
    closeText.setFillColor(BLACK);
    closeText.setCharacterSize(20);
    closeText.setPosition(x + width - 28, y + 8);
    closeText.setFont(FontController::Monofur());
    CenterString(closeText, "X", x + width - 20);
    closeButton = Button(Vector2f(20, 20), Vector2f(x + width - 30, y + 10), WHITE, MOUSE_OVER_COLOR);
}

void Status::Draw()
{
    bool changeSize;
    if (Selection != NONE_SELECTED)
    {
        changeSize = Grow();
    }
    else
    {
        if (Shrink()) return;
        changeSize = true;
    }
    CoreController::SfmlController()->DrawShape(rect);
    if (!changeSize) 
    {
        DrawChildren();
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        mousePressed = false;
    }
}

void Status::DrawChildren()
{
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
    if (closeButton.Draw())
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
            Selection = NONE_SELECTED;
        }
    }
    CoreController::SfmlController()->DrawString(closeText);

}

void Status::DrawSystem()
{
    title.setString(SYSTEM_NAMES[int(SelectedSystem)]);
    CoreController::SfmlController()->DrawString(title);

    if (SelectedPlot == nullptr || SelectedPlot->GetPlotType() != nullptr) return;
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

    CenterString(buttonText, "Build", x + float(width) / 2);
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
                CoreController::GetSystemController()
                    ->GetSystem(SelectedPlot->GetPlotType()->SystemType)->Destroy(SelectedPlot);
                CoreController::GetSystemController()->Plots()->ClearSelections();
            }
        }
    }

    CenterString(buttonText, "Destroy", x + float(width) / 2);
    CoreController::SfmlController()->DrawString(buttonText);
}

bool Status::Grow()
{
    if (changeHeight != height)
    {
        changeHeight += 10;
        rect.setSize(Vector2f(rect.getSize().x, changeHeight));
        return true;
    }
    return false;
}

bool Status::Shrink()
{
    if (changeHeight != 0)
    {
        changeHeight -= 10;
        rect.setSize(Vector2f(rect.getSize().x, changeHeight));
        return false;
    }
    return true;
}
