#include "PlotSystem.h"
#include "../../Helpers/Constants.h"
#include "../../Controllers/CoreController.h"


PlotSystem::PlotSystem()
{
    for (int i = LEFT; i < RIGHT; ++i)
    {
        const int left = std::max(LEFT - i, LEFT);
        const int right = std::min(RIGHT - i, RIGHT);
        for (int j = left; j < right; ++j)
        {
            const int k = -i - j;
            auto plot = new Plot(i,j,k);
            plots.InsertLast(plot);                
        }
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
        auto & shape = plot->GetShape();
        CoreController::Instance()->SfmlController()->DrawCircle(shape);
    }
}


/**
 * \brief Attemps to find a plot in the system with the corresponding coordinates
 * \param coords Coordinates of the plot to find
 * \return Returns the plot if found, or nullptr if not
 */
Plot* PlotSystem::FindPlot(const Coordinate& coords) const
{
    for (auto && plot : plots)
    {
        if (plot->Coords() == coords)
        {
            return plot;
        }
    }
    return nullptr;
}

/**
 * \brief Gets a random plot for the system
 * \return Random Plot
 */
Plot* PlotSystem::GetRandomPlot() const
{
    const int rand = CoreController::RandomInt(0, plots.Count());
    return plots[rand];
}

/**
 * \brief Checks if the click was on a plot and handles it if applicable
 * \return True if the click was handled
 */
bool PlotSystem::HandleClick() const
{
    for (auto && plot : plots)
    {
        if (plot->InBounds())
        {
            plot->Click();
            return true;
        }
    }    
    
    return false;
}
