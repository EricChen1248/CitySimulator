#include "PlotSystem.h"
#include "../../Helpers/Constants.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/PathFinder/PathFinder.h"

PlotSystem::PlotSystem(): hoverPlot(nullptr), builtBridge(true)
{
    const int size = RIGHT - LEFT;
    plotArray = new Plot**[size];
    for (int i = 0; i < size; ++i)
    {
        plotArray[i] = new Plot*[size] {nullptr};
    }
    
    for (int i = LEFT; i < RIGHT; ++i)
    {
        const int left = std::max(LEFT - i, LEFT);
        const int right = std::min(RIGHT - i, RIGHT);
        for (int j = left; j < right; ++j)
        {
            const int k = -i - j;
            auto plot = new Plot(i, j, k);
            plots.InsertLast(plot);
            plotArray[i - LEFT][j - LEFT] = plot;
        }
    }

    for (auto && plot : plots)
    {
        plot->GenerateRoads();
        PathFinder::MapPlot(plot);
    }
}

PlotSystem::~PlotSystem()
{
    plots.Dispose();
};


/**
 * \brief Renders all the plots
 */
void PlotSystem::Render() const
{
    for (auto && plot : plots)
    {
        auto & shape = plot->UpdateShape();
        CoreController::SfmlController()->DrawShape(shape);
    }
}

void PlotSystem::RenderInterDay()
{
    for (auto && plot : plots)
    {
        auto & shape = plot->UpdateShape();
        CoreController::SfmlController()->DrawShape(shape);
    }
    HandleClick();
}


/**
 * \brief Attemps to find a plot in the system with the corresponding coordinates
 * \param coords Coordinates of the plot to find
 * \return Returns the plot if found, or nullptr if not
 */
Plot* PlotSystem::FindPlot(const Coordinate& coords) const
{
    return CoordToPlotArray(coords);
}

/**
 * \brief Gets a random plot for the system
 * \return Random Plot
 */
Plot* PlotSystem::GetRandomPlot() const
{
    const int rand = RandomInt(0, plots.Count());
    return plots[rand];
}

/**
 * \brief Checks if the click was on a plot and handles it if applicable
 */
void PlotSystem::HandleClick()
{
    const auto window = CoreController::SfmlController()->Window();
    const auto view = CoreController::GetViewportController();
    const auto mousePos = sf::Mouse::getPosition(*window);
    if (mousePos.x < 0 || mousePos.y < 0 || mousePos.x > WINDOW_WIDTH || mousePos.y > WINDOW_HEIGHT)
    {
        return;
    }
    const auto adjustedMousePos = window->mapPixelToCoords(mousePos, view->GameView());
    if (hoverPlot != nullptr)
    {
        auto & shape = hoverPlot->GetShape();
        // If still over plot
        if (shape.getGlobalBounds().contains(adjustedMousePos.x, adjustedMousePos.y))
        {
			
            // if mouse is clicked
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (Status::SelectedPlot != nullptr)
                {
                    auto & selectedShape = Status::SelectedPlot->GetShape();
                    selectedShape.setOutlineThickness(0);
                }
                Status::SelectedPlot = hoverPlot;
                if (hoverPlot->currentType != nullptr)
                {
                    Status::Selection = PLOT;
                }
                shape.setOutlineColor(BLACK);
                shape.setOutlineThickness(3);
            }
        }
        else 
        {
            // has left plot
            // if plot is not selected, remove outline
            if (hoverPlot != Status::SelectedPlot)
            {
                shape.setOutlineThickness(0);
            }
            hoverPlot = nullptr;
        }
        // Mouse only just left plot, no need to check if over other plots
        return;
    }
    
    FindHoverPlot();
}

void PlotSystem::FindHoverPlot()
{
    const auto window = CoreController::SfmlController()->Window();
    const auto view = CoreController::GetViewportController();
    const auto mousePos = sf::Mouse::getPosition(*window);
    const auto adjustedMousePos = window->mapPixelToCoords(mousePos, view->GameView());
    for (auto && plot : plots)
    {
        auto & shape = plot->GetShape();
        if (shape.getGlobalBounds().contains(adjustedMousePos.x, adjustedMousePos.y))
        {
            hoverPlot = plot;
            if (hoverPlot != Status::SelectedPlot)
            {
                shape.setOutlineColor(LIGHT_GREY);
                shape.setOutlineThickness(3);
            }
            return;
        }
    }
}

void PlotSystem::ClearSelections()
{
    if (hoverPlot != nullptr)
    {
        auto & shape = hoverPlot->GetShape();
        shape.setOutlineThickness(0);
        hoverPlot = nullptr;
    }
    if (Status::SelectedPlot != nullptr)
    {
        auto & shape = Status::SelectedPlot->GetShape();
        shape.setOutlineThickness(0);
        Status::SelectedPlot = nullptr;
    }
           
    Status::Selection = NONE_SELECTED;
}

void PlotSystem::EndDay()
{
    for (auto && plot : plots)
    {
        plot->EndDay();
    }
    if (builtBridge)
    {
    }
}

Plot* PlotSystem::CoordToPlotArray(const Coordinate& coords) const
{
    if (coords.X() < LEFT || coords.X() >= RIGHT) return nullptr;
    if (coords.Y() < LEFT || coords.Y() >= RIGHT) return nullptr;
    if (coords.Z() < LEFT || coords.Z() >= RIGHT) return nullptr;
    return plotArray[coords.X() - LEFT][coords.Y() - LEFT];
}
