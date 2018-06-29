#include "SchoolRule.h"
#include "../../Controllers/CoreController.h"
#include "SchoolSystem.h"
#include "School.h"
#include "../../Helpers/HelperFunctions.h"

SchoolRule::SchoolRule(Citizen& citizen): BaseRule(citizen, SCHOOL), hungerLevel(0)
{
}

SchoolRule::~SchoolRule() = default;

float SchoolRule::CalculateScore()
{
    return 0;
}

/**
 * \brief Attemps to find a plot that can satisfy this rule
 * \return True if successfully found a plot to satisfy rule, otherwise false
 */
bool SchoolRule::FindPlot()
{
    auto &plots = CoreController::Instance()->GetSystemController()->GetSystem(FOOD)->Plots();
    
    // Get a list of plots that fulfill out requirements ( distance < max distance
    List<Plot*> choices;
    for (auto && plot : plots)
    {
        auto coords = citizen->Coords();
        const auto distance = plot->Coords().Distance(coords);
        if (distance < maxDistance)
        {
            auto p = plot;
            choices.InsertLast(p);
        }
    }
    
    // If such a list doesn't exist. This rule returns failed result false
    if (choices.Count() == 0)
    {
        return false;
    }
    const auto chosen = choices[RandomInt(0, choices.Count())];
    citizen->SetActiveRule(this);
    citizen->SetTarget(chosen);
    
    return true;
}

void SchoolRule::EnterPlot(Plot* plot)
{
    // TODO: Implement properly!!!
    return;
    const auto food = dynamic_cast<School*>(plot->GetPlotType());
    citizen->Wait(1.f);
    citizen->IncreaseMoney(-food->cost);
    food->Enter();
}

/**
 * \brief Fills up the citizen's hunger on leaving
 * \param plot Plot thats is being left. Redudant. Only for interface requirements
 */
void SchoolRule::LeavePlot(Plot* plot)
{
    hungerLevel = 100.f;
}

/**
 * \brief Update events of food rule. Decreases citizen's hunger
 */
void SchoolRule::Update()
{
    // TODO : Tweak hunger to time ratio
    hungerLevel -= CoreController::Instance()->GetDeltaTime() * 240;
}

/**
 * \brief Returns bool to tell if citizen is satisfied with it's food requirements
 * \return True if hunger level is over 20
 */
bool SchoolRule::IsSatisfied()
{
    return true;
}

int SchoolRule::getEdLvl()
{
    return EdLvl;    
}
