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
    
    void HandleClick();
	void FindHoverPlot();
    void ClearSelections();
    
    void NewDay() {};
    void EndDay();
    
    const LinkedList<Plot*>& Plots() const { return plots; }
    Plot* FindPlot(const Coordinate& coords) const;
    Plot* GetRandomPlot() const;
private:
    Plot* CoordToPlotArray(const Coordinate& coords) const;
    
    Plot*** plotArray;
    LinkedList<Plot*> plots;
    Plot* hoverPlot;
    bool builtBridge;
};

