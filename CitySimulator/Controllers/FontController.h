#pragma once
#include <SFML/Graphics/Font.hpp>

/**
 * \brief Loads and stores all used fonts in game
 */
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

