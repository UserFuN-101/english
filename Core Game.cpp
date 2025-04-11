#include "Core Game.h"
#include <iostream>

Game::Game() :
    isFullscreen(false),
    window(sf::VideoMode(800, 600), "Word Shuffle"),
    currentScreen(nullptr),
    mainMenuScreen(nullptr),
    difficultyScreen(nullptr),
    inputScreen(nullptr),
    gameScreen(nullptr),
    resultScreen(nullptr)
{
    // Загрузка шрифта
    if (!font.loadFromFile("../resources/fonts/arial.ttf")) {
        std::cerr << "Failed to load font \"resources/fonts/arial.ttf\"" << std::endl;
    }

    // Загрузка фона
    if (!backgroundTexture.loadFromFile("../resources/images/fon2.jpg")) {
        std::cerr << "Failed to load background \"resources/images/background.jpg\"" << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
        // Scale the background to fit the window
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );
    }
    
    // Create screens
    mainMenuScreen = new MainMenuScreen(font, [this](Screen* screen) { switchScreen(screen); });
    difficultyScreen = new DifficultyScreen(font, [this](Screen* screen) { switchScreen(screen); });
    currentScreen = mainMenuScreen; // Start on the main menu
}

void Game::toggleFullscreen() {
    isFullscreen = !isFullscreen;
    sf::Vector2u oldSize = window.getSize(); // Запоминаем старый размер окна

    window.close();

    if (isFullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), "Word Shuffle", sf::Style::Fullscreen);
    }
    else {
        window.create(sf::VideoMode(800, 600), "Word Shuffle", sf::Style::Default);
    }

    updateBackgroundScale();
    updateScreenScale(oldSize, window.getSize()); // Масштабируем элементы
}

void Game::updateScreenScale(sf::Vector2u oldSize, sf::Vector2u newSize) {
    float scaleX = static_cast<float>(newSize.x) / oldSize.x;
    float scaleY = static_cast<float>(newSize.y) / oldSize.y;
}


void Game::updateBackgroundScale() {
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );
}

Game::~Game() {
    delete currentScreen;
    if (!mainMenuScreen) delete mainMenuScreen;
    delete difficultyScreen;
    delete inputScreen;
    delete gameScreen;
    delete resultScreen;
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processInput();
        update(deltaTime);
        render();
    }
}

void Game::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (currentScreen) {
            currentScreen->handleInput(event, window);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11) {
            toggleFullscreen();
        }
    }
}

void Game::update(float deltaTime) {
    if (currentScreen) {
        currentScreen->update(deltaTime);
    }
}

void Game::render() {
    window.clear(sf::Color::White);

    // Draw background
    window.draw(backgroundSprite);

    if (currentScreen) {
        currentScreen->draw(window);
    }

    window.display();
}

void Game::switchScreen(Screen* newScreen) {
    if (currentScreen != nullptr && currentScreen != mainMenuScreen) {
        delete currentScreen;
    }
    currentScreen = newScreen;
}