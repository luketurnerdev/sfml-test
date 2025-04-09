//
// Created by luke on 9/04/2025.
//
#include <SFML/Graphics.hpp>
#include "snakeGame.h"

#include "Food.h"
#include "MoveableObject.h"

void CheckForWindowEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void MovePlayerBasedOnKeyPresses(MoveableObject& player, const float& movementIncrement) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        player.setPosition(Position{player.getPosition().x + movementIncrement,player.getPosition().y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        player.setPosition(Position{player.getPosition().x - movementIncrement,player.getPosition().y});
    }

    // Y positions are reversed because SFML draws the plane from the top left corner
    // i.e., a positive change in y means we are moving down

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        player.setPosition(Position{player.getPosition().x, player.getPosition().y + movementIncrement});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        player.setPosition(Position{player.getPosition().x, player.getPosition().y - movementIncrement});
    }
}

void DrawSpriteToScreen(const sf::Sprite& sprite, sf::RenderWindow& window) {
    window.draw(sprite);
}

void SetInitialSpritePos(sf::Sprite& sprite, const float& startingXPos, const float& startingYPos) {
    const sf::Vector2f startingPos = {startingXPos, startingYPos};
    sprite.setPosition(startingPos);
}

void SetPlayerBoundaries(sf::RenderWindow& window) {
    // Get the size of the window from the window instance
    // this will define the minimum and maximum X and Y values
    // We can assume the window will not be resized for this example
}

void runSnakeGame() {
    // Setup window
    sf::RenderWindow window(sf::VideoMode({800,600}), "SFML Test", sf::Style::Titlebar);
    // SetPlayerBoundaries(window);

    // Init player
    const sf::Texture characterTexture("img/sword32.png");
    constexpr Position startPosition = {0,0};
    const float movementIncrement = 0.05f;
    MoveableObject player(characterTexture, startPosition);

    //Init food (sample)
    const sf::Texture foodTexture("img/banana32.png");
    constexpr Position spawnPosition = {100,100};
    Food food(foodTexture, spawnPosition);

    while (window.isOpen()) {
        // Check for events
        CheckForWindowEvents(window);
        MovePlayerBasedOnKeyPresses(player, movementIncrement);

        // Drawing //

        // Clear anything previously drawn
        window.clear(sf::Color::Black);

        // Render whatever we want to
        DrawSpriteToScreen(player.getSprite(), window);
        DrawSpriteToScreen(food.getSprite(), window);

        // Display the current frame with what was drawn
        window.display();
    }
}