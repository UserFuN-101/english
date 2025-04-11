#ifndef DIFFICULTYSCREEN_H
#define DIFFICULTYSCREEN_H

#include <SFML/Graphics.hpp>
#include "UI Screen.h"
#include "UI Button.h"
#include <functional>

class DifficultyScreen : public Screen {
public:
    DifficultyScreen(sf::Font& font, std::function<void(Screen*)> switchScreenCallback);
    ~DifficultyScreen() override;

    void draw(sf::RenderWindow& window) override;
    void handleInput(sf::Event& event, sf::RenderWindow& window) override;
    void update(float deltaTime) override;

    bool isDifficultySelected() const;
    sf::String getSelectedDifficulty() const;

private:
    sf::Font& font;
    Button* easyButton;
    Button* mediumButton;
    Button* hardButton;
    Button* backButton;
    std::function<void(Screen*)> switchScreenCallback;

    sf::String selectedDifficulty;
    bool difficultySelected;
};

#endif // DIFFICULTYSCREEN_H