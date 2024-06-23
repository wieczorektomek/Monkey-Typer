#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Ranking {
public:
    Ranking(const std::string& rankingFile);
    void run();

private:
    void processEvents();
    void render();
    void loadRankingFile(const std::string& rankingFile);

    sf::RenderWindow window_;
    sf::Font font_;
    sf::Text titleText_;
    sf::Text rankingText_;
    std::vector<std::string> rankingData_;
    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;
};
