#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Word : public sf::Text {
public:
    Word(const std::string& word, const sf::Font& font);

    void move(const sf::Vector2f& offset);
};
