#include "UI Button.h"

Button::Button(const sf::Vector2f& position, sf::Font& font, const sf::String& textString) :
    font(font)
{
    button.setPosition(position);
    button.setSize(UIConstants::BUTTON_SIZE);
    button.setFillColor(UIConstants::BUTTON_FILL_COLOR);
    button.setOutlineColor(UIConstants::BUTTON_OUTLINE_COLOR);
    button.setOutlineThickness(UIConstants::BUTTON_OUTLINE_THICKNESS);

    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(UIConstants::BUTTON_TEXT_SIZE);
    text.setFillColor(UIConstants::BUTTON_TEXT_COLOR);
    text.setPosition(position.x + UIConstants::BUTTON_TEXT_OFFSET_X, position.y + UIConstants::BUTTON_TEXT_OFFSET_Y);

    normalColor = sf::Color(200, 200, 200);
    highlightedColor = sf::Color(100, 100, 255);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

bool Button::isClicked(const sf::Vector2f& mousePosition) const {
    return button.getGlobalBounds().contains(mousePosition);
}

void Button::setPosition(const sf::Vector2f& position) {
    button.setPosition(position);
    text.setPosition(position.x + UIConstants::BUTTON_TEXT_OFFSET_X, position.y + UIConstants::BUTTON_TEXT_OFFSET_Y);
}

void Button::setHighlighted(bool highlighted) {
    if (highlighted) {
        button.setFillColor(highlightedColor);
    }
    else {
        button.setFillColor(normalColor);
    }
}

void Button::scale(float scaleX, float scaleY) {
    button.setSize({ button.getSize().x * scaleX, button.getSize().y * scaleY });
    button.setPosition({ button.getPosition().x * scaleX, button.getPosition().y * scaleY });
    text.setCharacterSize(static_cast<unsigned int>(text.getCharacterSize() * scaleY));
    text.setPosition({ text.getPosition().x * scaleX, text.getPosition().y * scaleY });
}

