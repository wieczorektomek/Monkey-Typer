#include <SFML/Graphics.hpp>
#include "Ranking.h"

class Menu {
public:
    Menu();
    void run();

private:
    void processEvents();
    void render();
    bool shouldRunGame() const;

    sf::RenderWindow window_;
    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    sf::Font titlefont_;
    sf::Font font_;
    sf::Text titleText_;
    sf::Text playText_;
    sf::Text optionsText_;
    sf::Text rankingText_;
    sf::RectangleShape playButton_;
    sf::RectangleShape optionsButton_;
    sf::RectangleShape rankingButton_;
    bool shouldRunGame_;
    bool shouldRunRanking_;
    int selectedOption_;


    void resetMenu() {
        shouldRunGame_ = false;
        selectedOption_ = 0;
    }
};

