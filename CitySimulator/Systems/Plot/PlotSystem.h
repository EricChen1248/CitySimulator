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
    void Render();
    Plot* FindPlot(const Coordinate& coords);
    // TODO : Make plots private
    //private:
    List<Plot*> plots;
};

