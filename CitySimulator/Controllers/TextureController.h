#pragma once
#include "SFMLController.h";

class TextureController
{
public:
    TextureController(SFMLController* sfmlController);
    ~TextureController();
private:
    SFMLController* sfmlController;
};

