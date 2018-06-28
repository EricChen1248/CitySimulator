#include "FontController.h"
#include "../Assets/Fonts/Monofur.h"


FontController* FontController::instance;

FontController::FontController()
{
    instance = this;
    monofur.loadFromMemory(&monofur_regular_ttf, monofur_regular_ttf_len);   
}


FontController::~FontController() = default;