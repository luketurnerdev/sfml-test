//
// Created by luke on 9/04/2025.
//
#include <SFML/Graphics.hpp>
#include "snakeGame.h"

#include <iostream>

#include "CollisionManager.h"
#include "Food.h"
#include "Utils.h"
#include "MoveableObject.h"

void CheckForWindowEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void MovePlayerBasedOnKeyPresses(MoveableObject& player, sf::RenderWindow& window) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        player.setPosition(Position{player.getPosition().x + player.getMovementIncrement(),player.getPosition().y}, window);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        player.setPosition(Position{player.getPosition().x - player.getMovementIncrement(),player.getPosition().y}, window);
    }

    // Y positions are reversed because SFML draws the plane from the top left corner
    // i.e., a positive change in y means we are moving down

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        player.setPosition(Position{player.getPosition().x, player.getPosition().y + player.getMovementIncrement()}, window);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        player.setPosition(Position{player.getPosition().x, player.getPosition().y - player.getMovementIncrement()}, window);
    }
}

void DrawSpriteToScreen(const sf::Sprite& sprite, sf::RenderWindow& window) {
    window.draw(sprite);
}

void SetInitialSpritePos(sf::Sprite& sprite, const float& startingXPos, const float& startingYPos) {
    const sf::Vector2f startingPos = {startingXPos, startingYPos};
    sprite.setPosition(startingPos);
}

void runSnakeGame() {
    // Setup window
    sf::RenderWindow window(sf::VideoMode({800,600}), "SFML Test", sf::Style::Titlebar);

    // Init player
    const sf::Texture characterTexture("img/sword32.png");
    constexpr Position startPosition = {0,0};
    constexpr float playerMovementIncrement = 0.05f;
    MoveableObject player(characterTexture, startPosition, playerMovementIncrement);

    //Init food (sample)
    const sf::Texture foodTexture("img/banana32.png");
    constexpr Position spawnPosition = {100,100};
    Food food(foodTexture, spawnPosition);

    // Register collisions
    CollisionManager collisionManager;
    collisionManager.RegisterObject("Player", &player);
    collisionManager.RegisterObject("Food", &food);

    collisionManager.RegisterCollisionCallback("Player", "Food", []() {
       std::cout << "Nom nom!" << std::endl;
    });

    while (window.isOpen()) {
        // Check for events
        CheckForWindowEvents(window);
        MovePlayerBasedOnKeyPresses(player, window);

        // Drawing //

        // Clear anything previously drawn
        window.clear(sf::Color::Black);

        // Boundary and collision stuff
        player.setBoundary();
        food.setBoundary();
        collisionManager.CheckCollisions();

        // Render whatever we want to
        DrawSpriteToScreen(player.getSprite(), window);
        DrawSpriteToScreen(food.getSprite(), window);



        // Display the current frame with what was drawn
        window.display();
    }
}