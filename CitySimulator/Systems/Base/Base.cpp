#include "Base.h"
#include "BaseSystem.h"
#include "../../Helpers/Constants.h"

Base::Base(Plot* plot, const System system): SystemType(system)
{
    this->plot = plot;
    color = BLACK;
    score = 0;
}

int Base::Destroy()
{
    CoreController::GetSystemController()->GetSystem(SystemType)->Unregister(plot);
    return 0;
}
