#include "Menu.h"
#include "WordGame.h"

Menu::Menu() :
        window_(sf::VideoMode(1200, 600), "MonkeyTyper menu"),
        shouldRunGame_(false), // Domyślnie ustawiamy na false
        selectedOption_(0) // Domyślnie wybieramy opcję "Play"
{
    backgroundTexture_.loadFromFile("../MonkeyTyper/assets/background.png");
    backgroundSprite_.setTexture(backgroundTexture_);
    titlefont_.loadFromFile("../MonkeyTyper/assets/creamy.ttf");
    font_.loadFromFile("../MonkeyTyper/assets/Cute Dino.ttf");

    titleText_.setFont(titlefont_);
    titleText_.setCharacterSize(70);
    titleText_.setFillColor(sf::Color::White);
    titleText_.setOutlineThickness(4);
    titleText_.setString("MonkeyTyper");

    titleText_.setPosition(window_.getSize().x / 2 - titleText_.getGlobalBounds().width / 2, 150);

    playText_.setFont(font_);
    playText_.setCharacterSize(30);
    playText_.setFillColor(sf::Color::White);
    playText_.setString("PLAY");

    rankingText_.setFont(font_);
    rankingText_.setCharacterSize(30);
    rankingText_.setFillColor(sf::Color::White);
    rankingText_.setString("RANKING");
}

void Menu::run() {
    while (window_.isOpen()) {
        processEvents();
        render();

        if (shouldRunGame_) {
            WordGame wordGame;
            wordGame.run();
            shouldRunGame_ = false; // Reset flagi po zakończeniu gry
        } else if (shouldRunRanking_) {
            auto rankingFile = std::string();
            Ranking ranking(rankingFile);
            ranking.run();
            shouldRunRanking_ = false; // Reset flagi po zakończeniu rankingu
        }
    }
}

void Menu::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                if (selectedOption_ > 0) {
                    selectedOption_--;
                }
            } else if (event.key.code == sf::Keyboard::Down) {
                if (selectedOption_ < 1) { // Zmiana na maksymalną wartość 1
                    selectedOption_++;
                }
            } else if (event.key.code == sf::Keyboard::Return) {
                if (selectedOption_ == 0) {
                    shouldRunGame_ = true;
                } else if (selectedOption_ == 1) {
                    shouldRunRanking_ = true;
                }
            }
        }
    }
}

void Menu::render() {
    window_.clear();

    window_.draw(backgroundSprite_);
    window_.draw(titleText_);

    // Ustawienie właściwości przycisku "Play"
    playButton_.setSize(sf::Vector2f(300, 50));
    playButton_.setPosition(window_.getSize().x / 2 - playButton_.getSize().x / 2, window_.getSize().y / 2 - playButton_.getSize().y / 2);
    playButton_.setFillColor(sf::Color(127, 176, 59));

    // Ustawienie konturu przycisku
    playButton_.setOutlineThickness(4);  // Grubość konturu
    playButton_.setOutlineColor(sf::Color::White);  // Kolor konturu

    // Zmiana koloru podświetlenia w zależności od wybranej opcji
    if (selectedOption_ == 0) {
        playButton_.setFillColor(sf::Color(39, 53, 19)); // Podświetlenie, gdy wybrana opcja to "Play"
    }

    // Ustawienie właściwości tekstu na przycisku "Play"
    playText_.setPosition(playButton_.getPosition() + sf::Vector2f((playButton_.getSize().x - playText_.getGlobalBounds().width) / 2, (playButton_.getSize().y - playText_.getGlobalBounds().height) / 2));
    window_.draw(playButton_);
    window_.draw(playText_);

    // Ustawienie właściwości przycisku "Ranking"
    rankingButton_.setSize(sf::Vector2f(300, 50));
    rankingButton_.setPosition(window_.getSize().x / 2 - rankingButton_.getSize().x / 2, window_.getSize().y / 2 + 50);
    rankingButton_.setFillColor(sf::Color(127, 176, 59));
    rankingButton_.setOutlineThickness(4);
    rankingButton_.setOutlineColor(sf::Color::White);

    // Zmiana koloru podświetlenia w zależności od wybranej opcji
    if (selectedOption_ == 1) {
        rankingButton_.setFillColor(sf::Color(39, 53, 19)); // Podświetlenie, gdy wybrana opcja to "Ranking"
    }

    // Ustawienie właściwości tekstu na przycisku "Ranking"
    rankingText_.setPosition(rankingButton_.getPosition() + sf::Vector2f((rankingButton_.getSize().x - rankingText_.getGlobalBounds().width) / 2, (rankingButton_.getSize().y - rankingText_.getGlobalBounds().height) / 2));
    window_.draw(rankingButton_);
    window_.draw(rankingText_);
    window_.display();
}



bool Menu::shouldRunGame() const {
    return shouldRunGame_;
}
