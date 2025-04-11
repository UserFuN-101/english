#include "UI DifficultyScreen.h"
#include "UI InputScreen.h"
#include "UI MainMenuScreen.h" // Добавьте эту строку
#include <iostream>

DifficultyScreen::DifficultyScreen(sf::Font& font, std::function<void(Screen*)> switchScreenCallback) :
    font(font),
    switchScreenCallback(switchScreenCallback),
    selectedDifficulty(""),
    difficultySelected(false)
{
    easyButton = new Button({ 100, 100 }, font, L"Легко");
    mediumButton = new Button({ 100, 170 }, font, L"Средне");
    hardButton = new Button({ 100, 240 }, font, L"Сложно");
    backButton = new Button({ 100, 310 }, font, L"Назад");  // Initially hidden
}

DifficultyScreen::~DifficultyScreen() {
    delete easyButton;
    delete mediumButton;
    delete hardButton;
    delete backButton;
}

void DifficultyScreen::draw(sf::RenderWindow& window) {
    easyButton->draw(window);
    mediumButton->draw(window);
    hardButton->draw(window);
    backButton->draw(window);

}

void DifficultyScreen::handleInput(sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (easyButton->isClicked(mousePos)) {
            selectedDifficulty = L"Легко";
            difficultySelected = true;
            std::cout << "Difficulty: Easy" << std::endl;
            backButton->setPosition({ 100, 310 });  // Show back button
            if (switchScreenCallback) {
                switchScreenCallback(new InputScreen(font, selectedDifficulty, switchScreenCallback));
            }
        }
        else if (mediumButton->isClicked(mousePos)) {
            selectedDifficulty = L"Средне";
            difficultySelected = true;
            std::cout << "Difficulty: Medium" << std::endl;
            backButton->setPosition({ 100, 310 });
            if (switchScreenCallback) {
                switchScreenCallback(new InputScreen(font, selectedDifficulty, switchScreenCallback));
            }
        }
        else if (hardButton->isClicked(mousePos)) {
            selectedDifficulty = L"Сложно";
            difficultySelected = true;
            std::cout << "Difficulty: Hard" << std::endl;
            backButton->setPosition({ 100, 310 });
            if (switchScreenCallback) {
                switchScreenCallback(new InputScreen(font, selectedDifficulty, switchScreenCallback));
            }
        }
        else if (backButton->isClicked(mousePos)) {
            difficultySelected = false;
            selectedDifficulty = "";
            std::cout << "Back to Main Menu" << std::endl;
            backButton->setPosition({ -100, -100 }); // Hide back button
            if (switchScreenCallback) {
                switchScreenCallback(new MainMenuScreen(font, switchScreenCallback));
            }
        }
    }
}

void DifficultyScreen::update(float deltaTime) {
    // No specific update logic needed for this screen
}

bool DifficultyScreen::isDifficultySelected() const {
    return difficultySelected;
}

sf::String DifficultyScreen::getSelectedDifficulty() const {
    return selectedDifficulty;
}
