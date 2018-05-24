#pragma once
#include <SFML/Graphics/Font.hpp>

class FontController
{
public:
    FontController();
    ~FontController();


    const sf::Font& Monofur() const
    {
        return monofur;
    }

private:
    sf::Font monofur;
};

