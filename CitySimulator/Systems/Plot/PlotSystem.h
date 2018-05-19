#pragma once
#include "Plot.h"
#include "../../Collections/List.h"

class PlotSystem
{
public:
    PlotSystem();
    ~PlotSystem();
    void Render() const;
private:
    List<Plot*> *plots;
};

