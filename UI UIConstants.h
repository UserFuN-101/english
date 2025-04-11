#ifndef UICONSTANTS_H
#define UICONSTANTS_H

#include <SFML/Graphics.hpp>

namespace UIConstants {
    // Button
    const sf::Vector2f BUTTON_SIZE = { 200, 50 };
    const sf::Color BUTTON_FILL_COLOR = sf::Color::White;
    const sf::Color BUTTON_OUTLINE_COLOR = sf::Color::Black;
    const float BUTTON_OUTLINE_THICKNESS = 2.0f;
    const unsigned int BUTTON_TEXT_SIZE = 24;
    const sf::Color BUTTON_TEXT_COLOR = sf::Color::Black;
    const float BUTTON_TEXT_OFFSET_X = 10.0f;
    const float BUTTON_TEXT_OFFSET_Y = 5.0f;

    // Input Field
    const sf::Vector2f INPUT_FIELD_SIZE = { 600, 50 };
    const sf::Color INPUT_FIELD_FILL_COLOR = sf::Color::White;
    const sf::Color INPUT_FIELD_OUTLINE_COLOR = sf::Color::Black;
    const float INPUT_FIELD_OUTLINE_THICKNESS = 2.0f;
    const unsigned int INPUT_TEXT_SIZE = 20;
    const sf::Color INPUT_TEXT_COLOR = sf::Color::Black;
    const float INPUT_TEXT_OFFSET_X = 10.0f;
    const float INPUT_TEXT_OFFSET_Y = 5.0f;
} // namespace UIConstants

#endif