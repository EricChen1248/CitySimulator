#pragma once
#include "Plot.h"
#include "../../Collections/List.h"

/**
 * \brief Plot system that stores and handles the collective plots in the game
 */
class PlotSystem
{
public:
    PlotSystem();
    ~PlotSystem();
    void Render() const;
    void RenderInterDay();
    Plot* FindPlot(const Coordinate& coords) const;
    Plot* GetRandomPlot() const;
    void HandleClick();
    void ClearSelections();
private:
    List<Plot*> plots;
    Plot* hoverPlot;
    Plot* selectedPlot;;
};

