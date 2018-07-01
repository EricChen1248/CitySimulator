#pragma once
#include "Plot.h"
#include "../../Collections/LinkedList.h"

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
	void FindHoverPlot();
    void ClearSelections();
    void EndDay();
	const LinkedList<Plot*>& Plots() const { return plots; };

private:
    Plot* CoordToPlotArray(const Coordinate& coords) const;
    
    Plot*** plotArray;
    LinkedList<Plot*> plots;
    Plot* hoverPlot;
    Plot* selectedPlot;
    bool builtBridge;
};

