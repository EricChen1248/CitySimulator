#include "PlotSystem.h"
#include "../../Controllers/CoreController.h"


PlotSystem::PlotSystem()
{
    plots = new List<Plot*>();
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            for (int k = 0; k < 5; ++k)
            {
                auto plot = new Plot(i,j,k);
                plots->InsertLast(plot);
            }
        }
    }
}

PlotSystem::~PlotSystem() = default;

void PlotSystem::Render() const
{
    for (int i = 0; i < plots->Count(); ++i)
    {
        auto shape = (*plots)[i]->GetShape();
        CoreController::Instance()->SfmlController()->DrawCircle(shape);
    }
}
