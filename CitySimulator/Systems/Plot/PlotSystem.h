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
    void GenerateRoads();

    void Render() const;
    void RenderInterDay();
	void RenderRoads() const;
    
    void HandleClick();
	void FindHoverPlot();
    void ClearSelections();
    
    void NewDay() {};
    void EndDay();
    
    const LinkedList<Plot*>& Plots() const { return plots; }
	const List<Road*>& Roads() const { return roads; }
    Plot* FindPlot(const Coordinate& coords) const;
    Plot* GetRandomPlot() const;

private:
    Plot* CoordToPlotArray(const Coordinate& coords) const;
    Plot*** plotArray;
    LinkedList<Plot*> plots;
	List<Road*> roads;
    Plot* hoverPlot;
    bool builtBridge;
};

