#include "UI GameScreen.h"
#include "UI ResultScreen.h"
#include <iostream>
#include <algorithm>
#include <random>
#include "Utils.h"
#include "InputFieldHandler.h"

GameScreen::GameScreen(sf::Font& font, const sf::String& difficulty, const std::vector<std::string>& sentences, std::function<void(Screen*)> switchScreenCallback) :
    font(font),
    difficulty(difficulty),
    sentences(sentences),
    currentSentenceIndex(0),
    switchScreenCallback(switchScreenCallback),
    isInputFieldSelected(true),
    inputField(UIConstants::INPUT_FIELD_SIZE),
    inputText("", font, UIConstants::INPUT_TEXT_SIZE),
    cursorVisible(true),
    cursorTimer(0.0f),
    inputFieldHandler(inputText, cursorVisible, cursorTimer)
{
    nextButton = new Button({ 100, 202 }, font, L"�����");
    finishButton = new Button({ 100, 202 }, font, L"��������� ����");
    inputField.setPosition(100, 150);
    inputField.setFillColor(UIConstants::INPUT_FIELD_FILL_COLOR);
    inputField.setOutlineColor(UIConstants::INPUT_FIELD_OUTLINE_COLOR);
    inputField.setOutlineThickness(UIConstants::INPUT_FIELD_OUTLINE_THICKNESS);
    inputText.setPosition(110, 160);
    inputText.setFillColor(UIConstants::INPUT_TEXT_COLOR);
    shuffledSentenceText.setFont(font);
    shuffledSentenceText.setCharacterSize(UIConstants::INPUT_TEXT_SIZE);
    shuffledSentenceText.setFillColor(UIConstants::INPUT_TEXT_COLOR);
    shuffledSentenceText.setPosition(110, 110);

    shuffleSentences();
    shuffleWordsAndLetters();
    shuffledSentenceText.setString(shuffledSentences[currentSentenceIndex]);
}

GameScreen::~GameScreen() {
    delete nextButton;
    delete finishButton;
}

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(inputField);
    window.draw(inputText);
    window.draw(shuffledSentenceText);
    if (currentSentenceIndex < sentences.size() - 1) {
        nextButton->draw(window);
    }
    else {
        finishButton->draw(window);
    }
    if (isInputFieldSelected && cursorVisible) {
        sf::RectangleShape cursor(sf::Vector2f(2, UIConstants::INPUT_TEXT_SIZE));
        cursor.setPosition(inputText.findCharacterPos(currentInput.size()).x, inputText.getPosition().y);
        cursor.setFillColor(sf::Color::Black);
        window.draw(cursor);
    }
}

void GameScreen::handleInput(sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // ��������� ������� ���� � ��������� � ���������� �����������
        if (currentSentenceIndex < sentences.size() - 1 && nextButton->isClicked(mousePos)) {
            std::string inputWithoutLineBreaks = removeLineBreaks(currentInput);
            std::string trimmedInput = trim(inputWithoutLineBreaks);
            userSentences.push_back(trimmedInput);
            currentInput = "";
            inputFieldHandler.resetInput();
            currentSentenceIndex++;
            shuffledSentenceText.setString(shuffledSentences[currentSentenceIndex]);
        }
        // ����������� ����
        else if (currentSentenceIndex == sentences.size() - 1 && finishButton->isClicked(mousePos)) {
            std::string inputWithoutLineBreaks = removeLineBreaks(currentInput);
            std::string trimmedInput = trim(inputWithoutLineBreaks);
            userSentences.push_back(trimmedInput);
            if (switchScreenCallback) {
                switchScreenCallback(new ResultScreen(font, sentences, userSentences, switchScreenCallback));
            }
        }
    }

    if (isInputFieldSelected && event.type == sf::Event::TextEntered) {
        // ���������� ���������� ������� � ��������� ������� ����� Ctrl + V
        if (event.text.unicode < 128 && event.text.unicode > 31) { // ��������� ������ �������� ASCII �������
            if (event.text.unicode == 8) { // Backspace
                if (!currentInput.empty()) {
                    currentInput.pop_back();
                }
            }
            else {
                currentInput += static_cast<char>(event.text.unicode);
            }
            inputText.setString(currentInput);
        }
    }

    // ��������� ��������� ������� ����� Ctrl + V
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.control && event.key.code == sf::Keyboard::V) {
            std::cout << "CTRLV!" << std::endl;
        }
    }


    if (isInputFieldSelected && event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Return) {
            // ��������� ������� ���� � ��������� � ���������� �����������
            if (currentSentenceIndex < sentences.size() - 1) {
                std::string inputWithoutLineBreaks = removeLineBreaks(currentInput);
                std::string trimmedInput = trim(inputWithoutLineBreaks);
                userSentences.push_back(trimmedInput);
                currentInput = "";
                inputFieldHandler.resetInput();
                currentSentenceIndex++;
                shuffledSentenceText.setString(shuffledSentences[currentSentenceIndex]);
            }
            // ����������� ����
            else if (currentSentenceIndex == sentences.size() - 1) {
                std::string inputWithoutLineBreaks = removeLineBreaks(currentInput);
                std::string trimmedInput = trim(inputWithoutLineBreaks);
                userSentences.push_back(trimmedInput);
                if (switchScreenCallback) {
                    switchScreenCallback(new ResultScreen(font, sentences, userSentences, switchScreenCallback));
                }
            }
        }
    }
}

void GameScreen::update(float deltaTime) {
    inputFieldHandler.updateCursor(deltaTime);
    inputText.setString(currentInput);
}

void GameScreen::shuffleSentences() {
    shuffledSentences = sentences; // ��������� ������� �����������

    if (difficulty == L"�����") {
        shuffledSentences.resize(std::min(shuffledSentences.size(), size_t(5)));
    }
    else if (difficulty == L"������") {
        shuffledSentences.resize(std::min(shuffledSentences.size(), size_t(10)));
    }
    else if (difficulty == L"������") {
        shuffledSentences.resize(std::min(shuffledSentences.size(), size_t(15)));
    }
}

void GameScreen::shuffleWordsAndLetters() {
    std::random_device rd;
    std::mt19937 g(rd());

    for (auto& sentence : shuffledSentences) {
        std::vector<std::string> words;
        std::string word;

        for (char c : sentence) {
            if (c == ' ') {
                if (!word.empty()) words.push_back(word);
                word.clear();
            }
            else {
                word += c;
            }
        }
        if (!word.empty()) words.push_back(word); // ��������� ��������� �����

        if (difficulty == L"�����") {
            std::shuffle(words.begin(), words.end(), g);
        }
        else if (difficulty == L"������") {
            for (auto& w : words) {
                std::shuffle(w.begin(), w.end(), g);
            }
        }
        else if (difficulty == L"������") {
            std::shuffle(words.begin(), words.end(), g);
            for (auto& w : words) {
                std::shuffle(w.begin(), w.end(), g);
            }
        }

        sentence.clear();
        for (size_t i = 0; i < words.size(); ++i) {
            sentence += words[i];
            if (i < words.size() - 1) sentence += " "; // ��������� ������� ����� �������
        }
    }
}
