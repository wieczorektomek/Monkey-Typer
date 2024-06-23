#include "Word.h"

Word::Word(const std::string& word, const sf::Font& font) {
    setString(word);
    setFont(font);
    setCharacterSize(30);
    setFillColor(sf::Color(102, 51, 153));
}

void Word::move(const sf::Vector2f& offset) {
    sf::Text::move(offset);
}
