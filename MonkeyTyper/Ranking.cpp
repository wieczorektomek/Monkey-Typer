#include "Ranking.h"
#include <fstream>
#include <sstream>

Ranking::Ranking(const std::string& rankingFile) :
        window_(sf::VideoMode(800, 600), "Ranking")
{
    font_.loadFromFile("../MonkeyTyper/assets/Cute Dino.ttf");

    backgroundTexture_.loadFromFile("../MonkeyTyper/assets/rankingBackground.png");
    backgroundSprite_.setTexture(backgroundTexture_);

    titleText_.setFont(font_);
    titleText_.setCharacterSize(50);
    titleText_.setFillColor(sf::Color::White);
    titleText_.setString("Top Scores");
    titleText_.setOutlineThickness(3);
    titleText_.setPosition(window_.getSize().x / 2 - titleText_.getGlobalBounds().width / 2, 20);

    rankingText_.setFont(font_);
    rankingText_.setCharacterSize(30);
    rankingText_.setFillColor(sf::Color::White);
    rankingText_.setPosition(50, 100);

    loadRankingFile(rankingFile);

    std::stringstream ss;
    for (const auto& line : rankingData_) {
        ss << line << "\n";
    }
    rankingText_.setString(ss.str());
}

void Ranking::run() {
    while (window_.isOpen()) {
        processEvents();
        render();
    }
}

void Ranking::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
    }
}

void Ranking::render() {
    window_.clear();
    window_.draw(backgroundSprite_);
    window_.draw(titleText_);
    window_.draw(rankingText_);
    window_.display();
}

void Ranking::loadRankingFile(const std::string& rankingFile) {
    std::ifstream file(rankingFile);
    std::string line;
    while (std::getline(file, line)) {
        rankingData_.push_back(line);
    }
}
