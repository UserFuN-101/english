#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "UI Screen.h"
#include "UI MainMenuScreen.h"
#include "UI DifficultyScreen.h"
#include "UI InputScreen.h"
#include "UI GameScreen.h"
#include "UI ResultScreen.h"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void processInput();
    void update(float deltaTime);
    void render();

    void switchScreen(Screen* newScreen);
    bool isFullscreen;
    void toggleFullscreen();
    void updateScreenScale(sf::Vector2u oldSize, sf::Vector2u newSize);
    void updateBackgroundScale();
private:
    sf::RenderWindow window;
    Screen* currentScreen;

    sf::Font font;

    // Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Screens
    MainMenuScreen* mainMenuScreen;
    DifficultyScreen* difficultyScreen;
    InputScreen* inputScreen;
    GameScreen* gameScreen;
    ResultScreen* resultScreen;
};

#endif // GAME_H