#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

class Screen {
public:
    virtual ~Screen() {}

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleInput(sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) {}
};

#endif // SCREEN_H