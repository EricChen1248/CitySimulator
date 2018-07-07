#include "Status.hpp"
#include "../CoreController.h"
#include "../FontController.h"
#include "../SFMLController.h"
#include "../MouseController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Systems/Base/BaseSystem.h"
#include "../../Systems/Plot/PlotSystem.h"
#include "../../Helpers/Government.h"

Selection Status::Selection = NONE_SELECTED;
Plot* Status::SelectedPlot = nullptr;
Road* Status::SelectedRoad = nullptr;
System Status::SelectedSystem = NONE;
bool Status::buildMode;

Status::Status()
= default;

Status::~Status()
= default;

void Status::Init(const int x, const int y)
{
    this->x = x;
    this->y = y;
    width = int(float(WINDOW_WIDTH) / 2 - 255);

    rect.setPosition(float(x), float(y));
    rect.setFillColor(WHITE);
    rect.setOutlineColor(BLACK);
    rect.setOutlineThickness(2.f);
    rect.setSize(Vector2f(float(width), 0.f));

    title.setFillColor(BLACK);
    title.setCharacterSize(24);
    title.setPosition(x + 20.f, y + 10.f);
    title.setFont(FontController::Monofur());

    buttonText.setFillColor(BLACK);
    buttonText.setCharacterSize(20);
    buttonText.setPosition(x + 20.f, y + height - 34.f);
    buttonText.setFont(FontController::Monofur());
    
    leftButtonText.setFillColor(BLACK);
    leftButtonText.setCharacterSize(20);
    leftButtonText.setPosition(x + 20.f, y + height - 34.f);
    leftButtonText.setFont(FontController::Monofur());
    
    rightButtonText.setFillColor(BLACK);
    rightButtonText.setCharacterSize(20);
    rightButtonText.setPosition(x + 20.f, y + height - 34.f);
    rightButtonText.setFont(FontController::Monofur());
    
    content.setFillColor(BLACK);
    content.setCharacterSize(20);
    content.setPosition(x + 20.f, y + 42.f);
    content.setFont(FontController::Monofur());

    button = Button(Vector2f(width - 42.f, 28.f), Vector2f(x + 20.f, y + height - 34.f), WHITE, MOUSE_OVER_COLOR);
    leftButton = Button(Vector2f(width - 162.f, 28.f), Vector2f(x + 20.f, y + height - 34.f), WHITE, MOUSE_OVER_COLOR);
    rightButton = Button(Vector2f(width - 162.f, 28.f), Vector2f(x - 20.f + 162.f, y + height - 34.f), WHITE, MOUSE_OVER_COLOR);
    
    closeText.setFillColor(BLACK);
    closeText.setCharacterSize(20);
    closeText.setPosition(x + width - 28.f, y + 8.f);
    closeText.setFont(FontController::Monofur());
    
    CenterString(closeText, "X", x + width - 20.f);
    closeButton = Button(Vector2f(20.f, 20.f), Vector2f(x + width - 30.f, y + 10.f), WHITE, MOUSE_OVER_COLOR);
    
    buildMode = false;
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
}

void Status::Build(Plot* plot)
{
    CoreController::GetSystemController()->GetSystem(SelectedSystem)->Register(plot);
}

void Status::DrawChildren()
{
    switch (Selection)
    {
    case SYSTEM:
        DrawSystem();
        break;
    case PLOT:
        if (buildMode) ToggleBuildMode();
        DrawPlot();
        break;
    case ROAD: 
        if (buildMode) ToggleBuildMode();
        DrawRoad();
        break;
    default: ;
    }
    if (closeButton.Draw())
    {
        if (MouseController::IsClicked())
        {
            if (buildMode) ToggleBuildMode();
            Selection = NONE_SELECTED;
        }
    }
    CoreController::SfmlController()->DrawString(closeText);

}

void Status::ToggleBuildMode()
{
    buildMode = !buildMode;
    button.ReverseColor();
    rightButton.ReverseColor();
}

void Status::DrawSystem()
{
    title.setString(SYSTEM_NAMES[int(SelectedSystem)]);
    PlotSystem::DeselectPlotsAndRoads();
    CoreController::SfmlController()->DrawString(title);
    const auto system = CoreController::GetSystemController()->GetSystem(SelectedSystem);
    content.setString(system->ContentString());
    CoreController::SfmlController()->DrawString(content);
    if (system->Toggleable())
    {
        DrawDoubleButton(system);
    }
    else
    {
        DrawSingleButton();
    }
}

void Status::DrawDoubleButton(BaseSystem * system)
{
    if (leftButton.Draw())
    {
        if (MouseController::IsClicked())
        {
            system->Toggle();
        }
    }
    
    const int cost = CoreController::GetSystemController()->GetSystem(SelectedSystem)->Cost();
    const bool disable = Government::TaxDollars() < cost;
    if (disable)
    {
        rightButton.DisableOnce();
    }
    
    if (rightButton.Draw())
    {
        if (MouseController::IsClicked())
        {
            ToggleBuildMode();
        }
    }

    CenterString(leftButtonText, "Toggle", x + float(width) / 2 - 61);
    CoreController::SfmlController()->DrawString(leftButtonText);

    CenterString(rightButtonText, "Build", x + float(width) / 2 + 61);
    CoreController::SfmlController()->DrawString(rightButtonText);
}

void Status::DrawSingleButton()
{
    
    const int cost = CoreController::GetSystemController()->GetSystem(SelectedSystem)->Cost();
    const bool disable = Government::TaxDollars() < cost;
    if (disable)
    {
        button.DisableOnce();
    }
    if (button.Draw())
    {
        if (MouseController::IsClicked())
        {
            ToggleBuildMode();
        }
    }

    CenterString(buttonText, "Build", x + float(width) / 2);
    CoreController::SfmlController()->DrawString(buttonText);
}

void Status::DrawPlot()
{
    if (SelectedPlot == nullptr)
    {
        Selection = NONE_SELECTED;
        return;
    }
    if (SelectedPlot->GetPlotType() == nullptr) return;

    title.setString(SYSTEM_NAMES[int(SelectedPlot->GetPlotType()->SystemType)]);
    CoreController::SfmlController()->DrawString(title);
    content.setString(SelectedPlot->GetPlotType()->ContentString());
    CoreController::SfmlController()->DrawString(content);
    
    const int cost = SelectedPlot->GetPlotType()->Cost() / 2;
    std::stringstream ss;
    ss << " Destroy ($" << cost << ")";
    CenterString(buttonText, ss.str(), x + float(width) / 2);
    if (button.Draw())
    {
        if(MouseController::IsClicked())
        {
            CoreController::GetSystemController()
                ->GetSystem(SelectedPlot->GetPlotType()->SystemType)->Destroy(SelectedPlot);
            CoreController::GetSystemController()->Plots()->ClearSelections();
            Government::AddTax(cost);
        }
    }
    CoreController::SfmlController()->DrawString(buttonText);
}

void Status::DrawRoad()
{
    title.setString("Road");
    CoreController::SfmlController()->DrawString(title);
    content.setString(SelectedRoad->ContentString());
    CoreController::SfmlController()->DrawString(content);
    
    if (button.Draw())
    {
        if (MouseController::IsClicked())
        {
            SelectedRoad->PerformClick();
        }
    }

    CenterString(buttonText, SelectedRoad->ButtonString(), x + float(width) / 2);
    CoreController::SfmlController()->DrawString(buttonText);
}

bool Status::Grow()
{
    if (changeHeight != height)
    {
        changeHeight += 10;
        rect.setSize(Vector2f(float(rect.getSize().x), float(changeHeight)));
        return true;
    }
    return false;
}

bool Status::Shrink()
{
    if (changeHeight != 0)
    {
        changeHeight -= 10;
        rect.setSize(Vector2f(float(rect.getSize().x), float(changeHeight)));
        return false;
    }
    return true;
}
