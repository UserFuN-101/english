#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include <SFML/Graphics.hpp>
#include "UI Screen.h"
#include "UI Button.h"
#include <functional>

class MainMenuScreen : public Screen {
public:
    MainMenuScreen(sf::Font& font, std::function<void(Screen*)> switchScreenCallback);
    ~MainMenuScreen() override;

    void draw(sf::RenderWindow& window) override;
    void handleInput(sf::Event& event, sf::RenderWindow& window) override;
    void update(float deltaTime) override;
private:
    sf::Font& font;
    Button* startButton;
    Button* exitButton;
    Button* russianButton;
    Button* englishButton;
    std::function<void(Screen*)> switchScreenCallback;
    bool selectedLanguage; // true = Русский, false = English
    sf::Text fullscreenText;
    
};

#endif // MAINMENUSCREEN_H