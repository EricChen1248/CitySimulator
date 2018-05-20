#include "PlotSystem.h"
#include "../../Controllers/CoreController.h"


PlotSystem::PlotSystem()
{
    int left = -20;
    int right = 21;
    
#ifdef _DEBUG
    left = -15;
    right = 16;
#endif
    
    for (int i = left; i < right; ++i)
    {
        for (int j = left; j < right; ++j)
        {
            for (int k = left; k < right; ++k)
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
        auto & shape = plots[i]->GetShape();
        CoreController::Instance()->SfmlController()->DrawCircle(shape);
    }
}


/**
 * \brief Attemps to find a plot in the system with the corresponding coordinates
 * \param coords Coordinates of the plot to find
 * \return Returns the plot if found, or nullptr if not
 */
Plot* PlotSystem::FindPlot(const Coordinate& coords)
{
    for (int i = 0; i < plots.Count(); ++i)
    {
        if (plots[i]->Coords() == coords)
        {
            return plots[i];
        }
    }
    return nullptr;
}
