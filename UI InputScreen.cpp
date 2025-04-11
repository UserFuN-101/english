#include "UI InputScreen.h"
#include "UI GameScreen.h"
#include "UI DifficultyScreen.h"
#include "InputFieldHandler.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
#include "Utils.h"

std::vector<std::string> predefinedSentences = {
    "The cat sits on the window",
    "The sun shines brightly",
    "I love reading books",
    "The car drives down the road",
    "Birds sing in the morning",
    "Rain drips on the roof",
    "The weather is beautiful today",
    "We walk in the park",
    "The dog barks at passersby",
    "Winter has brought snow",
    "Leaves fall from the trees",
    "I am writing a letter to a friend",
    "The river flows to the sea",
    "Children play in the yard",
    "The wind sways the grass"
};



InputScreen::InputScreen(sf::Font& font, const sf::String& difficulty, std::function<void(Screen*)> switchScreenCallback) :
    font(font),
    difficulty(difficulty),
    switchScreenCallback(switchScreenCallback),
    isInputFieldSelected(false),
    inputField(UIConstants::INPUT_FIELD_SIZE),
    inputText("", font, UIConstants::INPUT_TEXT_SIZE),
    cursorVisible(true),
    cursorTimer(0.0f),
    saveMessage("", font, UIConstants::INPUT_TEXT_SIZE),
    errorMessage("", font, UIConstants::INPUT_TEXT_SIZE),
    inputFieldHandler(inputText, cursorVisible, cursorTimer)
{
    saveButton = new Button({ 100, 102 }, font, L"Сохранить");
    startButton = new Button({ 300, 102 }, font, L"Начать игру");
    backButton = new Button({ 500, 102 }, font, L"Назад");
    inputField.setPosition(100, 50);
    inputField.setFillColor(UIConstants::INPUT_FIELD_FILL_COLOR);
    inputField.setOutlineColor(UIConstants::INPUT_FIELD_OUTLINE_COLOR);
    inputField.setOutlineThickness(UIConstants::INPUT_FIELD_OUTLINE_THICKNESS);
    inputText.setPosition(110, 60); 
    inputText.setFillColor(UIConstants::INPUT_TEXT_COLOR);
    placeholderText.setFont(font);
    placeholderText.setString(L"Введите текст");
    placeholderText.setCharacterSize(UIConstants::INPUT_TEXT_SIZE);
    placeholderText.setFillColor(sf::Color(128, 128, 128));
    placeholderText.setPosition(110, 60); 
    saveMessage.setPosition(110, 160); 
    saveMessage.setFillColor(sf::Color::Black); // цвет текста для сообщения о сохранении
    errorMessage.setPosition(110, 160); // местоположения сообщения об ошибке
    errorMessage.setFillColor(sf::Color::Red); // цвет сообщения ошибки
    randomButton = new Button({ 300, 500 }, font, L"Случайные");
}

InputScreen::~InputScreen() {
    delete saveButton;
    delete startButton;
    delete backButton;
    delete randomButton;
}

void InputScreen::draw(sf::RenderWindow& window) {
    window.draw(inputField);
    window.draw(inputText);
    if (currentInput.empty() && !isInputFieldSelected) {
        window.draw(placeholderText);
    }
    saveButton->draw(window);
    startButton->draw(window);
    backButton->draw(window);
    randomButton->draw(window);
    if (isInputFieldSelected && cursorVisible) {
        sf::RectangleShape cursor(sf::Vector2f(2, UIConstants::INPUT_TEXT_SIZE));
        cursor.setPosition(inputText.findCharacterPos(currentInput.size()).x, inputText.getPosition().y);
        cursor.setFillColor(sf::Color::Black);
        window.draw(cursor);
    }
    window.draw(saveMessage);
    window.draw(errorMessage); // Отрисовка сообщения об ошибке
}

void InputScreen::handleInput(sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

    int maxSentences = 5; // Easy
    if (difficulty == L"Средне") maxSentences = 10;
    else if (difficulty == L"Сложно") maxSentences = 15;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (inputField.getGlobalBounds().contains(mousePos)) {
            isInputFieldSelected = true;
        }
        else {
            isInputFieldSelected = false;
        }

        if (randomButton->isClicked(mousePos)) {
            sentences.clear();
            std::random_shuffle(predefinedSentences.begin(), predefinedSentences.end());

            for (int i = 0; i < maxSentences; ++i) {
                sentences.push_back(predefinedSentences[i]);
            }
            saveMessage.setString(L"Добавлены случайные предложения");
            errorMessage.setString("");

            // После добавления предложений, сразу начинаем игру
            if (switchScreenCallback) {
                switchScreenCallback(new GameScreen(font, difficulty, sentences, switchScreenCallback));
            }
        }

        else if (saveButton->isClicked(mousePos) && sentences.size() < maxSentences) {
            std::string inputWithoutLineBreaks = removeLineBreaks(currentInput);
            std::string trimmedInput = trim(inputWithoutLineBreaks);
            if (trimmedInput.empty()) {
                errorMessage.setString(L"Пожалуйста, введите текст перед сохранением");
                saveMessage.setString("");
            }
            else {
                sentences.push_back(trimmedInput);
                std::cout << "Sentence saved: " << trimmedInput << std::endl;
                saveMessage.setString(L"Предложение " + std::to_wstring(sentences.size()) + L" сохранено");
                errorMessage.setString("");
                currentInput = "";
                inputFieldHandler.resetInput();
                isInputFieldSelected = true;
            }
        }
        else if (saveButton->isClicked(mousePos) && sentences.size() >= maxSentences) {
            errorMessage.setString(L"Достигнуто максимальное количество предложений (" + std::to_wstring(maxSentences) + L")");
            saveMessage.setString("");
        }
        else if (startButton->isClicked(mousePos)) {
            std::cout << "Start game button clicked" << std::endl;
            if (sentences.empty()) {
                errorMessage.setString(L"Пожалуйста, введите хотя бы одно предложение перед началом игры");
                saveMessage.setString("");
            }
            else if (switchScreenCallback) {
                switchScreenCallback(new GameScreen(font, difficulty, sentences, switchScreenCallback));
            }
        }
        else if (backButton->isClicked(mousePos)) {
            std::cout << "Back button clicked" << std::endl;
            if (switchScreenCallback) {
                switchScreenCallback(new DifficultyScreen(font, switchScreenCallback));
            }
        }
    }

    if (isInputFieldSelected && event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) { // ASCII characters only
            char enteredChar = static_cast<char>(event.text.unicode);

            if (enteredChar == 8) { // Backspace
                if (!currentInput.empty()) {
                    currentInput.pop_back();
                }
            }
            else if (std::isprint(enteredChar)) { // Проверяем, является ли символ печатным
                currentInput += enteredChar;
            }

            inputText.setString(currentInput);
        }
    }
    

    if (isInputFieldSelected && event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::V && event.key.control) {
            if (OpenClipboard(nullptr)) {
                HANDLE hClipboardData = GetClipboardData(CF_TEXT);
                if (hClipboardData) {
                    char* pchData = (char*)GlobalLock(hClipboardData);
                    if (pchData) {
                        currentInput += pchData;
                        GlobalUnlock(hClipboardData);
                    }
                }
                CloseClipboard();
            }
            inputText.setString(currentInput);
        }
        else if (event.key.code == sf::Keyboard::Return) {
            if (sentences.size() < maxSentences) {
                std::string inputWithoutLineBreaks = removeLineBreaks(currentInput);
                std::string trimmedInput = trim(inputWithoutLineBreaks);
                if (trimmedInput.empty()) {
                    errorMessage.setString(L"Пожалуйста, введите текст перед сохранением");
                    saveMessage.setString("");
                }
                else {
                    sentences.push_back(trimmedInput);
                    std::cout << "Sentence saved: " << trimmedInput << std::endl;
                    saveMessage.setString(L"Предложение " + std::to_wstring(sentences.size()) + L" сохранено");
                    errorMessage.setString("");
                    currentInput = "";
                    inputFieldHandler.resetInput();
                    isInputFieldSelected = true;
                }
            }
            else {
                errorMessage.setString(L"Достигнуто максимальное количество предложений (" + std::to_wstring(maxSentences) + L")");
                saveMessage.setString("");
            }
        }
    }
}

void InputScreen::update(float deltaTime) {
    inputFieldHandler.updateCursor(deltaTime);
    inputText.setString(currentInput);
}

bool InputScreen::isReadyToStart() const {
    return !sentences.empty();
}

std::vector<std::string> InputScreen::getSentences() const {
    return sentences;
}