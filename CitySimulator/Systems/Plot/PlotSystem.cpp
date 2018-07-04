#include "PlotSystem.h"
#include "../../Helpers/Constants.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/PathFinder/PathFinder.h"
#include "../../Helpers/FeatureFlags.h"
PlotSystem::PlotSystem(): hoverPlot(nullptr), hoverRoad(nullptr), builtBridge(true)
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

    for (auto&& plot : plots)
    {
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
#if !INVISIBLERIVER
		if (plot->IsRiver()) continue;
#endif
		auto & shape = plot->UpdateShape();
		CoreController::SfmlController()->DrawShape(shape);
	}
}

void PlotSystem::RenderInterDay()
{
    for (auto && plot : plots)
    {
		if (plot->IsRiver()) continue;
        auto & shape = plot->UpdateShape();
        CoreController::SfmlController()->DrawShape(shape);
    }

    HandleClick();
}

void PlotSystem::RenderRoads() const
{
	for (auto && road : roads)
	{
		road->Render();
	}
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
    bool onPlot = false;
    const auto window = CoreController::SfmlController()->Window();
    const auto view = CoreController::GetViewportController();
    const auto mousePos = sf::Mouse::getPosition(*window);
    
    if (mousePos.x < 0 || mousePos.y < 0 || mousePos.x > WINDOW_WIDTH || mousePos.y > WINDOW_HEIGHT) return;
    if (CoreController::GetUIController()->IsOverUI()) return;
    
    const auto adjustedMousePos = window->mapPixelToCoords(mousePos, view->GameView());
    const float x = adjustedMousePos.x, y = adjustedMousePos.y;
    if (hoverPlot != nullptr)
    {
        auto & shape = hoverPlot->GetShape();
        // If still over plot
        if (shape.getGlobalBounds().contains(x, y))
        {
            onPlot = true;
            // if mouse is clicked
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (Status::SelectedPlot != nullptr)
                {
                    auto & selectedShape = Status::SelectedPlot->GetShape();
                    selectedShape.setOutlineThickness(0);
                }
                if (Status::SelectedRoad != nullptr)
                {
                    auto & selectedShape = Status::SelectedRoad->Shape();
                    selectedShape.ResetColor();
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
    }
    // If is on line, no need to check road
    if (hoverRoad != nullptr && !onPlot)
    {
        auto & shape = hoverRoad->Shape();
        if (shape.InSimpleBounds(x, y) && shape.InComplexBounds(x, y))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (Status::SelectedPlot != nullptr)
                {
                    auto & selectedShape = Status::SelectedPlot->GetShape();
                    selectedShape.setOutlineThickness(0);
                }
                if (Status::SelectedRoad != nullptr)
                {
                    auto & selectedShape = Status::SelectedRoad->Shape();
                    selectedShape.ResetColor();
                }
                Status::SelectedRoad = hoverRoad;
                Status::Selection = ROAD;
                
                shape.SetColor(BLACK);
            }
        }
        else 
        {
            if (hoverRoad != Status::SelectedRoad)
            {
                shape.ResetColor();
            }
            hoverRoad = nullptr;
        }
    }
    
    FindHover(x, y);
}

void PlotSystem::FindHover(const float x, const float y)
{
    for (auto && plot : plots)
    {
        auto & shape = plot->GetShape();
        if (shape.getGlobalBounds().contains(x, y))
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
    for (auto && road : roads)
    {
        auto & shape = road->Shape();
        if (shape.InSimpleBounds(x, y) && shape.InComplexBounds(x, y))
        {
            hoverRoad = road;
            if (hoverRoad != Status::SelectedRoad)
            {
                shape.SetColor(DARK_GREY);
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
    if (hoverRoad != nullptr)
    {
        auto & shape = hoverRoad->Shape();
        shape.ResetColor();
        hoverRoad = nullptr;
    }
    if (Status::SelectedRoad != nullptr)
    {
        auto & shape = Status::SelectedRoad->Shape();
        shape.ResetColor();
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
    for (auto road : roads)
    {
        road->EndDay();
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

void PlotSystem::GenerateRoads()
{
    for (auto&& plot : plots)
    {
        const auto neighbours = plot->Coords().GetNeighbours();
        for (int i = 0; i < 6; ++i)
        {
            const auto neighbour = FindPlot(neighbours[i]);
            if (neighbour != nullptr)
            {
                if (plot->roads[i] != nullptr) continue;
                Road* newRoad = new Road(plot, neighbour);
                plot->InsertNewRoad(newRoad, i);
                neighbour->InsertNewRoad(newRoad, 5 - i);
                roads.InsertLast(newRoad);
            }
        }
    }
}