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

Food SpawnFood(std::string texturePath, Position spawnPosition) {
    // Init food (sample)
    const sf::Texture foodTexture(texturePath);
    Food food(foodTexture, spawnPosition);

    // Set a static boundary for the food for collisions
    food.setBoundary();
    return food;
}

MoveableObject SpawnPlayer(const std::string& texturePath, const Position spawnPosition, const float playerMovementIncrement) {
    const sf::Texture characterTexture(texturePath);
    MoveableObject player(characterTexture, spawnPosition, playerMovementIncrement);

    return player;
}

void runSnakeGame() {
    // Setup window
    sf::RenderWindow window(sf::VideoMode({800,600}), "SFML Test", sf::Style::Titlebar);

    // Init player
    MoveableObject player = SpawnPlayer("img/sword32.png", {0,0}, 0.05f);

    // Spawn some food
    Food food = SpawnFood("img/banana32.png", {100,100});

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

        // Boundary and collision stuff
        collisionManager.CheckCollisions();

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