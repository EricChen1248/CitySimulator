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
    
    static void DeselectPlotsAndRoads();
    void HandleClick();
    void ClearSelections();
	void FindHover(float x, float y);
    void RoadClicks(bool onPlot, const float &x, const float &y);
    
    void NewDay();
    void EndDay();
    
	const List<Road*>& Roads() const { return roads; }
    const LinkedList<Plot*>& Plots() const { return plots; }
    
    Plot* FindPlot(const Coordinate& coords) const;
    Plot* GetRandomPlot() const;

private:
    Plot* CoordToPlotArray(const Coordinate& coords) const;
    Plot*** plotArray;
    LinkedList<Plot*> plots;
	List<Road*> roads;
    Plot* hoverPlot;
    Road* hoverRoad;
};

