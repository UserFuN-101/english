#ifndef INPUTFIELDHANDLER_H
#define INPUTFIELDHANDLER_H

#include <SFML/Graphics.hpp>

class InputFieldHandler {
public:
    InputFieldHandler(sf::Text& inputText, bool& cursorVisible, float& cursorTimer);
    void updateCursor(float deltaTime);
    void resetInput();

private:
    sf::Text& inputText;
    bool& cursorVisible;
    float& cursorTimer;
};

#endif