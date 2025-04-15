//
// Created by luke on 9/04/2025.
//
#include <SFML/Graphics.hpp>
#include "snakeGame.h"

#include <iostream>

#include "CollisionManager.h"
#include "Food.h"
#include "Player.h"
#include "Utils.h"
#include "MoveableObject.h"
#include "SpawnManager.h"

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

void SetupCollisions(CollisionManager &collisionManager, MoveableObject &player, Food *&food) {

    // Register collisions

    collisionManager.RegisterObject("Player", &player);
    collisionManager.RegisterObject("Food", food);

    collisionManager.RegisterCollisionCallback("Player", "Food", [&]() {
       std::cout << "Nom nom!" << std::endl;
        collisionManager.ClearOneObjectAndCallback(food);
        Food::DeleteFood(food);
    });

}

void Init() {

}
void runSnakeGame() {
    // Setup window
    sf::RenderWindow window(sf::VideoMode({800,600}), "SFML Test", sf::Style::Titlebar);

    // Spawn player
    MoveableObject player = Player::SpawnPlayer("img/sword32.png", {0,0}, 0.05f);

    // Spawn some food
    // sf::Texture foodTexture;
    // foodTexture.loadFromFile("img/banana32.png");
    // Food* food = Food::SpawnFood(foodTexture, {100,100});


    // Spawning system
    SpawnManager spawnManager;
    Food* food = spawnManager.spawnFoodInRandomLocation();

    // Collisions
    CollisionManager collisionManager;
    SetupCollisions(collisionManager, player, *&food);

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

        // Collision squares for visibility (optional)
        DrawBoundarySquareOnScreenThisFrame(player, window);

        // Don't try to render food if it has been eaten
        if (food != nullptr) {
            DrawBoundarySquareOnScreenThisFrame(*food, window);
            DrawSpriteToScreen(food->getSprite(), window);
        }

        // Display the current frame with what was drawn
        window.display();
    }
}