#ifndef RESULTSCREEN_H
#define RESULTSCREEN_H

#include <SFML/Graphics.hpp>
#include "UI Screen.h"
#include "UI Button.h"
#include <vector>
#include <string>
#include <functional>

class ResultScreen : public Screen {
public:
    ResultScreen(sf::Font& font, const std::vector<std::string>& originalSentences, const std::vector<std::string>& userSentences, std::function<void(Screen*)> switchScreenCallback);
    ~ResultScreen() override;

    void draw(sf::RenderWindow& window) override;
    void handleInput(sf::Event& event, sf::RenderWindow& window) override;
    void update(float deltaTime) override;

private:
    sf::Font& font;
    std::vector<std::string> originalSentences;
    std::vector<std::string> userSentences;
    Button* backButton;
    sf::Text resultText;
    std::function<void(Screen*)> switchScreenCallback;
    std::vector<sf::Text> sentenceTexts;
    float scrollOffset;
};

#endif // RESULTSCREEN_H