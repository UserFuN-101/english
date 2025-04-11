#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include "UI Screen.h"
#include "UI Button.h"
#include "InputFieldHandler.h"
#include <vector>
#include <string>
#include <functional>

class GameScreen : public Screen {
public:
    GameScreen(sf::Font& font, const sf::String& difficulty, const std::vector<std::string>& sentences, std::function<void(Screen*)> switchScreenCallback);
    ~GameScreen() override;

    void draw(sf::RenderWindow& window) override;
    void handleInput(sf::Event& event, sf::RenderWindow& window) override;
    void update(float deltaTime) override;

private:
    sf::Font& font;
    sf::String difficulty;
    std::vector<std::string> sentences;
    std::vector<std::string> shuffledSentences;
    std::vector<std::string> userSentences;
    int currentSentenceIndex;
    Button* nextButton;
    Button* finishButton;
    sf::Text shuffledSentenceText;
    sf::RectangleShape inputField;
    sf::Text inputText;
    sf::Text placeholderText;
    bool isInputFieldSelected;
    std::string currentInput;
    std::function<void(Screen*)> switchScreenCallback;
    bool cursorVisible;
    float cursorTimer;

    InputFieldHandler inputFieldHandler;

    void shuffleSentences();
    void shuffleWordsAndLetters();
};

#endif // GAMESCREEN_H