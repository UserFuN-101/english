#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "UI UIConstants.h"

class Button {
public:
    Button(const sf::Vector2f& position, sf::Font& font, const sf::String& text);
    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2f& mousePosition) const;
    void setPosition(const sf::Vector2f& position);
    void setHighlighted(bool highlighted);

    void scale(float scaleX, float scaleY);

private:
    sf::RectangleShape button;
    sf::Text text;
    sf::Font& font;
    sf::Color normalColor;
    sf::Color highlightedColor;
};

#endif // BUTTON_H