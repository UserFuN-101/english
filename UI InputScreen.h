#ifndef INPUTSCREEN_H
#define INPUTSCREEN_H

#include <SFML/Graphics.hpp>
#include "UI Screen.h"
#include "UI Button.h"
#include "InputFieldHandler.h" // Добавьте эту строку
#include <vector>
#include <string>
#include <functional>

class InputScreen : public Screen {
public:
    InputScreen(sf::Font& font, const sf::String& difficulty, std::function<void(Screen*)> switchScreenCallback);
    ~InputScreen() override;

    void draw(sf::RenderWindow& window) override;
    void handleInput(sf::Event& event, sf::RenderWindow& window) override;
    void update(float deltaTime) override;

    bool isReadyToStart() const;
    std::vector<std::string> getSentences() const;

private:
    sf::Font& font;
    sf::String difficulty;
    Button* saveButton;
    Button* startButton;
    Button* backButton;
    sf::RectangleShape inputField;
    sf::Text inputText;
    sf::Text placeholderText;
    sf::Text saveMessage;
    sf::Text errorMessage;
    bool isInputFieldSelected;
    std::string currentInput;
    std::vector<std::string> sentences;
    std::function<void(Screen*)> switchScreenCallback;
    bool cursorVisible;
    float cursorTimer;
    Button* randomButton;
    InputFieldHandler inputFieldHandler; // Добавьте эту строку
};

#endif // INPUTSCREEN_H