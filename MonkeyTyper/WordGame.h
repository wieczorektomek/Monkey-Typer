#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Word.h"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Sound.hpp"
#include <fmt/core.h>
#include <SFML/Audio.hpp>

class WordGame {
public:
    WordGame();
    void run();

private:
    sf::RenderWindow window_;
    sf::Font scoreboard_font_;
    sf::Font activeWord_font_;
    sf::Font inputWordFont_;
    sf::Texture backgroundTexture_;
    sf::Sprite backgroundSprite_;

    //SOUND

    sf::SoundBuffer rightAnwerBuffer_;
    sf::Sound rightAnswerSound_;

    sf::SoundBuffer liveLossSoundBuffer_;
    sf::Sound liveLossSound_;

    sf::SoundBuffer typingBuffer_;
    sf::Sound typingSound_;

    sf::Text inputText_;
    std::vector<std::vector<std::string>> mainVector_;

    std::vector<Word> activeWords_;
    int lives_;
    int points_;
    float speed_;
    int speedIncreaseInterval_;
    float speedIncreaseAmount_;
    float spawnIntervalInitial_;
    float spawnInterval_;
    float spawnIntervalDecreaseRate_;
    bool returnToMenu_;
    float wordFontSize_ = 35;
    sf::Clock clock_;
    sf::Clock spawnClock_;
    std::string inputWord_;
    sf::Texture livesIconTexture_;

    sf::Sprite livesIconSprite_;
    enum GameState { Playing, GameOver};
    GameState gameState_;

    int selectedGameOverOption_;
    sf::Text gameOverText_;
    sf::Text playAgainText_;

    sf::Text backToMenuText_;
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void checkLives();
    void handleGameOverEvent(sf::Event& event);
    void resetGame();

    void removeInvisibleCharacter(std::string& str) {
        str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    }

};
