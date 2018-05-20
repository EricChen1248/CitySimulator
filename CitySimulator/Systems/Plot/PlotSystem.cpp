#include "PlotSystem.h"
#include "../../Controllers/CoreController.h"


PlotSystem::PlotSystem()
{
    for (int i = -3; i < 4; ++i)
    {
        for (int j = -3; j < 4; ++j)
        {
            for (int k = -3; k < 4; ++k)
            {
                if (i + j + k == 0)
                {
                    auto plot = new Plot(i,j,k);
                    plots.InsertLast(plot);                
                }
            }
        }
    }
}

PlotSystem::~PlotSystem() = default;

void PlotSystem::Render()
{
    for (int i = 0; i < plots.Count(); ++i)
    {
        auto shape = plots[i]->GetShape();
        CoreController::Instance()->SfmlController()->DrawCircle(shape);
    }
}

Plot* PlotSystem::FindPlot(const Coordinate& coords)
{
    for (int i = 0; i < plots.Count(); ++i)
    {
        if (plots[i]->hasCoords(coords))
        {
            return plots[i];
        }
    }
    return nullptr;
}
