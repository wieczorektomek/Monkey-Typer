#include "WordGame.h"
#include "Word.h"
#include <iostream>
#include <fmt/format.h>

WordGame::WordGame() :
        window_(sf::VideoMode(1200, 600), "Monkey Typer"),
        lives_(3),
        points_(0),
        speed_(60.f),
        speedIncreaseInterval_(10),
        speedIncreaseAmount_(5.f),
        spawnIntervalInitial_(2.f),
        spawnInterval_(spawnIntervalInitial_),
        spawnIntervalDecreaseRate_(0.2f),
        gameState_(Playing),
        selectedGameOverOption_(0) // Initialize selected option
{


    if (!rightAnwerBuffer_.loadFromFile("../MonkeyTyper/assets/rightAnswer.wav")) {
        fmt::print("[ERROR] File not found\n");
    }

    rightAnswerSound_.setBuffer(rightAnwerBuffer_);

    if (!liveLossSoundBuffer_.loadFromFile("../MonkeyTyper/assets/wrongAnswer.wav")) {
        fmt::print("[ERROR] File not found\n");
    }
    liveLossSound_.setBuffer(liveLossSoundBuffer_);


    // Initialize random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Load font
    scoreboard_font_.loadFromFile("../MonkeyTyper/assets/Cooper-Black.ttf");
    activeWord_font_.loadFromFile("../MonkeyTyper/assets/Cute Dino.ttf");

    // Load background
    backgroundTexture_.loadFromFile("../MonkeyTyper/assets/background.png");
    backgroundSprite_.setTexture(backgroundTexture_);

    livesIconTexture_.loadFromFile("../MonkeyTyper/assets/heart.png");
    livesIconSprite_.setTexture(livesIconTexture_);

    // Initialize input text
    inputWordFont_.loadFromFile("../MonkeyTyper/assets/Bubblegum.ttf");
    inputText_.setFont(activeWord_font_);
    inputText_.setCharacterSize(35);
    inputText_.setFillColor(sf::Color::White);
    inputText_.setOutlineThickness(3);
    inputText_.setPosition(140, window_.getSize().y - 50);

    // Initialize vector of words
    auto fruits = std::vector<std::string>{"apple", "banana", "orange", "strawberry", "grape", "watermelon", "pineapple", "peach", "pear", "cherry", "kiwi", "mango", "blueberry", "raspberry", "lemon", "lime", "coconut", "plum", "apricot", "fig"};
    auto meansTransport = std::vector<std::string>{"car", "bus", "train", "bicycle", "motorcycle", "truck", "boat", "subway", "helicopter", "airplane", "scooter", "ferry", "taxi", "jet ski", "hovercraft", "rv", "tram", "segway", "skateboard", "hot air balloon"};
    auto animals = std::vector<std::string>{"dog", "cat", "elephant", "lion", "tiger", "bear", "zebra", "giraffe", "monkey", "rabbit", "snake", "crocodile", "hippopotamus", "penguin", "dolphin", "owl", "eagle", "shark", "octopus", "kangaroo"};
    auto vegetables = std::vector<std::string>{"carrot", "potato", "tomato", "cucumber", "lettuce", "spinach", "broccoli", "cauliflower", "onion", "garlic", "pepper", "eggplant", "zucchini", "mushroom", "celery", "radish", "cabbage", "sweet potato", "peas", "corn"};
    auto school_eq = std::vector<std::string>{"pen", "pencil", "notebook", "eraser", "ruler", "sharpener", "highlighter", "marker", "glue stick", "scissors", "calculator", "protractor", "compass", "dictionary", "backpack", "folder", "tape", "pencil case", "whiteboard", "chalk"};

    mainVector_ = {
            fruits,
            meansTransport,
            animals,
            vegetables,
            school_eq
    };

    // Initialize game over UI elements
    gameOverText_.setFont(scoreboard_font_);
    gameOverText_.setCharacterSize(70);
    gameOverText_.setFillColor(sf::Color::Red);
    gameOverText_.setString("GAME OVER");
    gameOverText_.setPosition(window_.getSize().x / 2 - gameOverText_.getGlobalBounds().width / 2, 100);

    playAgainText_.setFont(activeWord_font_);
    playAgainText_.setCharacterSize(50);
    playAgainText_.setFillColor(sf::Color::White);
    playAgainText_.setOutlineThickness(3);
    playAgainText_.setString("PLAY AGAIN");
    playAgainText_.setPosition(window_.getSize().x / 2 - playAgainText_.getGlobalBounds().width / 2, 300);

    backToMenuText_.setFont(activeWord_font_);
    backToMenuText_.setCharacterSize(50);
    backToMenuText_.setFillColor(sf::Color::White);
    backToMenuText_.setOutlineThickness(3);
    backToMenuText_.setString("BACK TO MENU");
    backToMenuText_.setPosition(window_.getSize().x / 2 - backToMenuText_.getGlobalBounds().width / 2, 400);
}

void WordGame::run() {
    while (window_.isOpen() && !returnToMenu_) {
        processEvents();
        if (gameState_ == Playing) {
            update(clock_.restart());
        }
        render();
    }

    // Przywracanie flagi returnToMenu do wartości domyślnej
    returnToMenu_ = false;
}

void WordGame::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        } else if (gameState_ == Playing) {
            if (event.type == sf::Event::TextEntered) {
                // Sprawdź, czy wprowadzany znak nie jest znakiem '+' lub '-'
                if ((event.text.unicode < 128 && event.text.unicode != 8) && event.text.unicode != '+' && event.text.unicode != '_') {
                    // ASCII
                    inputWord_ += static_cast<char>(event.text.unicode);
                    inputText_.setString(inputWord_);
                } else if (event.text.unicode == 8 && !inputWord_.empty()) { // backspace
                    inputWord_.pop_back();
                    inputText_.setString(inputWord_);
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Equal && event.key.shift) { // Shift + Plus
                    speed_ += 5;
                } else if ((event.key.code == sf::Keyboard::Hyphen || event.key.code == sf::Keyboard::Dash) && event.key.shift) { // Shift + Minus
                    speed_ -= 5;
                    if (speed_ < 5) // Limit speed to a minimum of 5
                        speed_ = 5;
                } else if (event.key.code == sf::Keyboard::Up && event.key.shift) { // Shift + Arrow Up
                    wordFontSize_ += 1; // Zwiększ rozmiar słów
                } else if (event.key.code == sf::Keyboard::Down && event.key.shift) { // Shift + Arrow Down
                    if (wordFontSize_ >= 11) // Limit font size to a minimum of 11
                        wordFontSize_ -= 1; // Zmniejsz rozmiar słów
                }
            }
        } else if (gameState_ == GameOver) {
            handleGameOverEvent(event);
        }
    }
}


void WordGame::update(sf::Time deltaTime) {
    // Sprawdź, czy nadszedł czas, aby stworzyć nowe słowo
    if (spawnClock_.getElapsedTime().asSeconds() > spawnInterval_) {
        spawnClock_.restart();

        // Wybierz losowe słowo z wektora
        auto losowyIndeksWektora = std::rand() % mainVector_.size();
        auto losowyIndeksSłowa = std::rand() % mainVector_[losowyIndeksWektora].size();
        auto wybraneSłowo = mainVector_[losowyIndeksWektora][losowyIndeksSłowa];

        // Stwórz słowo
        Word słowo(wybraneSłowo, activeWord_font_);
        słowo.setFillColor(sf::Color(255, 165, 0));
        słowo.setOutlineThickness(2);

        // Znajdź pozycję, która nie koliduje z istniejącymi słowami
        sf::Vector2f nowaPozycja;
        bool pozycjaPoprawna;
        int maksymalnePróby = 100; // Ograniczenie liczby prób, aby uniknąć nieskończonej pętli
        int próba = 0;
        int minimalnaOdległośćMiędzySłowami = 50; // Dostosowana odległość między słowami
        do {
            nowaPozycja = sf::Vector2f(0, 30 + std::rand() % 440); // Ogranicz pozycję wzdłuż osi Y
            pozycjaPoprawna = true;

            for (const auto& istniejąceSłowo : activeWords_) {
                // Sprawdź, czy nowe słowo jest wystarczająco daleko od istniejących słów
                if (std::abs(istniejąceSłowo.getPosition().y - nowaPozycja.y) < minimalnaOdległośćMiędzySłowami) {
                    pozycjaPoprawna = false;
                    break;
                }
            }

            próba++;
        } while (!pozycjaPoprawna && próba < maksymalnePróby);

        // Ustaw pozycję, jeśli znaleziono poprawną
        if (pozycjaPoprawna) {
            słowo.setPosition(nowaPozycja);
            activeWords_.push_back(słowo);
        }
    }

    // Zaktualizuj aktywne słowa
    for (auto& słowo : activeWords_) {
        float odległośćRuchu = speed_ * deltaTime.asSeconds();
        słowo.move(sf::Vector2f(odległośćRuchu, 0));

        // Ustaw nowy rozmiar słowa
        słowo.setCharacterSize(wordFontSize_);
    }

    // Usuń słowa, które wychodzą poza granice okna i zmniejsz liczbę żyć
    for (auto iter = activeWords_.begin(); iter != activeWords_.end();) {
        if (iter->getPosition().x > window_.getSize().x) {
            iter = activeWords_.erase(iter);
            --lives_;
            liveLossSound_.play();
            checkLives(); // Sprawdź życia po usunięciu słowa
        } else {
            ++iter;
        }
    }

    // Sprawdź dopasowania słów
    for (auto iter = activeWords_.begin(); iter != activeWords_.end(); ++iter) {
        if (inputWord_ == iter->getString()) {
            activeWords_.erase(iter); // Usuń słowo z activeWords
            inputWord_.clear(); // Wyczyść wprowadzone słowo
            inputText_.setString(inputWord_); // Wyczyść wprowadzony tekst
            ++points_; // Zwiększ punkty
            rightAnswerSound_.play();

            // Sprawdź, czy nadszedł czas zwiększenia prędkości
            if (points_ % speedIncreaseInterval_ == 0) {
                speed_ += speedIncreaseAmount_;
            }

            // Sprawdź, czy nadszedł czas zmniejszenia interwału pojawiania się
            if (points_ % speedIncreaseInterval_ == 0) {
                spawnInterval_ -= spawnIntervalDecreaseRate_;
                if (spawnInterval_ < 0.5f) // Ogranicz interwał pojawiania się do minimum 0.5 sekundy
                    spawnInterval_ = 0.5f;
            }

            break; // Przerwij pętlę po znalezieniu pierwszego dopasowania
        }
    }
}



void WordGame::render() {
    window_.clear();
    window_.draw(backgroundSprite_);

    if (gameState_ == Playing) {
        // Draw active words
        for (const auto& word : activeWords_) {
            auto wordText = word; // Skopiuj obiekt słowa, aby zachować oryginalny rozmiar
            wordText.setCharacterSize(wordFontSize_); // Ustaw nowy rozmiar słowa
            window_.draw(wordText);
        }

        // Scoreboard
        sf::Text wordTyping("Enter:", scoreboard_font_);
        wordTyping.setCharacterSize(35);
        wordTyping.setOutlineThickness(5);
        wordTyping.setPosition(10, window_.getSize().y - 50);
        window_.draw(wordTyping);
        window_.draw(inputText_);

        sf::Text pointsText("| Points:  " + std::to_string(points_), scoreboard_font_);
        pointsText.setCharacterSize(30);
        pointsText.setOutlineThickness(5);
        pointsText.setPosition(wordTyping.getGlobalBounds().width + 350, window_.getSize().y - 45);
        window_.draw(pointsText);

        sf::Text livesText("| Lives: ", scoreboard_font_);
        livesText.setCharacterSize(30);
        livesText.setOutlineThickness(5);
        livesText.setPosition(10 + pointsText.getGlobalBounds().width + 500, window_.getSize().y - 45);
        window_.draw(livesText);

        auto livesPositionX = livesText.getPosition().x + livesText.getGlobalBounds().width + 10;
        auto livesPositionY = livesText.getPosition().y;

        // Draw hearts
        sf::Sprite heartSprite(livesIconTexture_);
        heartSprite.setScale(0.7f, 0.7f);

        // Loop to draw hearts based on the number of lives
        for (int i = 0; i < lives_; ++i) {
            heartSprite.setPosition(livesPositionX + (heartSprite.getGlobalBounds().width * 0.7f + 20) * i, livesPositionY);
            window_.draw(heartSprite);
        }

        std::stringstream speedStream;
        speedStream << std::fixed << std::setprecision(2) << speed_;
        auto roundedSpeed = speedStream.str();

        sf::Text speedText("| Speed: " + roundedSpeed, scoreboard_font_);
        speedText.setCharacterSize(30);
        speedText.setOutlineThickness(5);
        speedText.setPosition(10 + livesText.getGlobalBounds().width + 850, window_.getSize().y - 45);
        window_.draw(speedText);

    } else if (gameState_ == GameOver) {
        // Draw game over screen
        window_.draw(gameOverText_);
        window_.draw(playAgainText_);
        window_.draw(backToMenuText_);

        // Highlight the selected option
        if (selectedGameOverOption_ == 0) {
            playAgainText_.setFillColor(sf::Color::Yellow);
            backToMenuText_.setFillColor(sf::Color::White);
        } else {
            playAgainText_.setFillColor(sf::Color::White);
            backToMenuText_.setFillColor(sf::Color::Yellow);
        }
    }

    window_.display();
}

void WordGame::checkLives() {
    if (lives_ <= 0) {
        // Game over logic
        gameState_ = GameOver;
    }
}

void WordGame::handleGameOverEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
            selectedGameOverOption_ = 1 - selectedGameOverOption_; // Przełączanie między 0 a 1
        } else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedGameOverOption_ == 0) {
                gameState_ = Playing; // Zmiana stanu gry na "Playing" po wybraniu "Play Again"
                resetGame();
            } else {
                returnToMenu_ = true; // Ustawienie flagi returnToMenu na true
                window_.close(); // Zamknięcie okna gry, aby powrócić do menu
            }
        }
    }
}

void WordGame::resetGame() {
    // Resetowanie stanu gry i zmiennych
    lives_ = 3;
    points_ = 0;
    speed_ = 60.f;
    spawnInterval_ = spawnIntervalInitial_;
    inputWord_.clear();
    removeInvisibleCharacter(inputWord_);
    inputText_.setString("");

    // Wyczyść aktywne słowa
    activeWords_.clear();

    gameState_ = Playing;
}