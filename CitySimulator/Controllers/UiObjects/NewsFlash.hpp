#pragma once
#include <string>
#include <SFML/Graphics/Text.hpp>

struct NewsFlash
{
public:
    NewsFlash();
    ~NewsFlash();
    void Render();
    void Flash(const std::string& str);    
private:
    sf::Text text;
    int left;
    int width;
    bool flash;
};

