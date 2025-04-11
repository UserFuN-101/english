#include "UI ResultScreen.h"
#include "UI MainMenuScreen.h"
#include <iostream>

ResultScreen::ResultScreen(sf::Font& font, const std::vector<std::string>& originalSentences, const std::vector<std::string>& userSentences, std::function<void(Screen*)> switchScreenCallback) :
    font(font),
    originalSentences(originalSentences),
    userSentences(userSentences),
    switchScreenCallback(switchScreenCallback)
{
    backButton = new Button({ 100, 100 }, font, L"�����");
    resultText.setFont(font);
    resultText.setCharacterSize(UIConstants::BUTTON_TEXT_SIZE);
    resultText.setFillColor(UIConstants::BUTTON_TEXT_COLOR);
    resultText.setPosition(100, 200);
    scrollOffset = 0;
    int correctCount = 0;
    for (size_t i = 0; i < originalSentences.size(); ++i) {
        if (originalSentences[i] == userSentences[i]) {
            correctCount++;
        }
    }

    resultText.setString(L"���������: " + std::to_wstring(correctCount) + L" �� " + std::to_wstring(originalSentences.size()));

    // ��������� ��������� ������� ��� ����������� �����������
    float yOffset = 250; // ��������� ������������ ������� ��� ������
    for (size_t i = 0; i < originalSentences.size(); ++i) {
        // ���������� �������� �����������
        sf::Text originalText;
        originalText.setFont(font);
        originalText.setString(L"��������: " + std::wstring(originalSentences[i].begin(), originalSentences[i].end()));
        originalText.setCharacterSize(20);
        originalText.setFillColor(sf::Color::Black);
        originalText.setPosition(100, yOffset);
        sentenceTexts.push_back(originalText);
        yOffset += 30;

        // ���������� ��������� ������������� �����������
        sf::Text userText;
        userText.setFont(font);
        userText.setString(L"��� �������: " + std::wstring(userSentences[i].begin(), userSentences[i].end()));
        userText.setCharacterSize(20);
        userText.setFillColor(sf::Color::Blue);  // ����� �������� ���� ��� ���������
        userText.setPosition(100, yOffset);
        sentenceTexts.push_back(userText);
        yOffset += 30;
    }
}

ResultScreen::~ResultScreen() {
    delete backButton;
}

void ResultScreen::draw(sf::RenderWindow& window) {
    backButton->draw(window);
    window.draw(resultText);

    for (const auto& sentenceText : sentenceTexts) {
        sf::Text text = sentenceText;
        text.setPosition(text.getPosition().x, text.getPosition().y - scrollOffset);  // ��������� ��������
        window.draw(text);
    }
}

void ResultScreen::handleInput(sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (backButton->isClicked(mousePos)) {
            std::cout << "Back button clicked" << std::endl;
            if (switchScreenCallback) {
                switchScreenCallback(new MainMenuScreen(font, switchScreenCallback));
            }
        }
    }
    // ��������� ���������
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            scrollOffset -= 30;  // ��������� �����
        }
        else {
            scrollOffset += 30;  // ��������� ����
        }

        // ������������ ���������, ����� ����� �� ������� �� �������
        scrollOffset = std::max(0.0f, scrollOffset);
        scrollOffset = std::min(scrollOffset, static_cast<float>(sentenceTexts.size()) * 90 - window.getSize().y);
    }
}

void ResultScreen::update(float deltaTime) {
    // No specific update logic needed for this screen
}