#pragma once
#include "../Base/BaseRule.h"
class WorkRule :
    public BaseRule
{
public:
    WorkRule(Citizen& citizen);
    ~WorkRule();
};

