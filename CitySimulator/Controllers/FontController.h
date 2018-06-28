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
    
    static const sf::Font& Monofur()
    {
        return instance->monofur;
    }

private:
    static FontController* instance;
    sf::Font monofur;
};

