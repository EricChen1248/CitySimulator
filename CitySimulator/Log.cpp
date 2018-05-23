#include "Log.h"
#include "Controllers/CoreController.h"

Log::Log(const Coordinate& coords, BaseRule* rule, ::Citizen* citizen)
{
    Coords = coords;
    Time = CoreController::Instance()->GetTime();
    Rule = rule;
    Citizen = citizen;
}
