#include "UI MainMenuScreen.h"
#include "UI DifficultyScreen.h"
#include <iostream>

MainMenuScreen::MainMenuScreen(sf::Font& font, std::function<void(Screen*)> switchScreenCallback) :
    font(font),
    switchScreenCallback(switchScreenCallback),
    selectedLanguage(false) // �� ��������� English
{
    startButton = new Button({ 100, 100 }, font, L"������");
    exitButton = new Button({ 100, 200 }, font, L"�����");

    russianButton = new Button({ 500, 100 }, font, L"�������");
    englishButton = new Button({ 500, 200 }, font, L"English");

    russianButton->setHighlighted(false);
    englishButton->setHighlighted(true);

    fullscreenText.setFont(font);
    fullscreenText.setCharacterSize(16);
    fullscreenText.setFillColor(sf::Color::Black);
    fullscreenText.setString(L"������� F11 ��� �������������� ������");
    fullscreenText.setPosition(100, 300);
}

MainMenuScreen::~MainMenuScreen() {
    delete startButton;
    delete exitButton;

    delete russianButton;
    delete englishButton;

}

void MainMenuScreen::draw(sf::RenderWindow& window) {
    if (!selectedLanguage) { // ���� ������ ����������, ���������� ������ "������"
        startButton->draw(window);
    }
    exitButton->draw(window);
    
    russianButton->draw(window);
    englishButton->draw(window);
    window.draw(fullscreenText); // ���������� ����� � ������������� ������
}

void MainMenuScreen::handleInput(sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (!selectedLanguage && startButton->isClicked(mousePos)) {
            std::cout << "Start button clicked" << std::endl;
            if (switchScreenCallback) {
                switchScreenCallback(new DifficultyScreen(font, switchScreenCallback));
            }
        }
        else if (exitButton->isClicked(mousePos)) {
            window.close();
        }
        else if (russianButton->isClicked(mousePos)) {
            selectedLanguage = "ru";
            russianButton->setHighlighted(true);
            englishButton->setHighlighted(false);
            std::cout << "Russian Game" << std::endl;
            selectedLanguage = true;
        }
        else if (englishButton->isClicked(mousePos)) {
            selectedLanguage = "en";
            russianButton->setHighlighted(false);
            englishButton->setHighlighted(true);
            std::cout << "English game" << std::endl;
            selectedLanguage = false;
        }
    }
}


void MainMenuScreen::update(float deltaTime) {
    // No specific update logic needed for this screen
}