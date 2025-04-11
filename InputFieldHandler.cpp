#include "InputFieldHandler.h"

InputFieldHandler::InputFieldHandler(sf::Text& inputText, bool& cursorVisible, float& cursorTimer) :
    inputText(inputText),
    cursorVisible(cursorVisible),
    cursorTimer(cursorTimer)
{
}

void InputFieldHandler::updateCursor(float deltaTime) {
    cursorTimer += deltaTime;
    if (cursorTimer >= 0.5f) {
        cursorVisible = !cursorVisible;
        cursorTimer = 0.0f;
    }
}

void InputFieldHandler::resetInput() {
    inputText.setString("");
}