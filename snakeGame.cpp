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

void ConstantlyMovePlayer(MoveableObject& player, sf::RenderWindow& window) {
    switch (player.getCurrentMovementDirection()) {
        case MoveableObject::MovementDirection::Right: {
            player.setPosition(Position{player.getPosition().x + player.getMovementIncrement(),player.getPosition().y}, window);
            break;
        }
        case MoveableObject::MovementDirection::Left: {
            player.setPosition(Position{player.getPosition().x - player.getMovementIncrement(),player.getPosition().y}, window);
            break;
        }

        // Note: Y positions are reversed because SFML draws the plane from the top left corner
        // i.e., a positive change in y means we are moving down

        case MoveableObject::MovementDirection::Up: {
            player.setPosition(Position{player.getPosition().x, player.getPosition().y - player.getMovementIncrement()}, window);
            break;
        }
        case MoveableObject::MovementDirection::Down: {
            player.setPosition(Position{player.getPosition().x, player.getPosition().y + player.getMovementIncrement()}, window);
            break;
        }
    }
}

void CheckForDirectionChanges(MoveableObject& player) {

    // change direction when user presses a key

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        player.setCurrentMovementDirection(MoveableObject::Right);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        player.setCurrentMovementDirection(MoveableObject::Left);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        player.setCurrentMovementDirection(MoveableObject::Down);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        player.setCurrentMovementDirection(MoveableObject::Up);
    }
}

void DrawSpriteToScreen(const sf::Sprite& sprite, sf::RenderWindow& window) {
    window.draw(sprite);
}

void SetInitialSpritePos(sf::Sprite& sprite, const float& startingXPos, const float& startingYPos) {
    const sf::Vector2f startingPos = {startingXPos, startingYPos};
    sprite.setPosition(startingPos);
}

void SetupCollisions(SpawnManager& spawnManager, CollisionManager &collisionManager, MoveableObject &player, Food *&food) {
    collisionManager.ClearOneObjectAndCallback(food);  // Get rid of any dangling references to old *foods

    collisionManager.RegisterObject("Player", &player);
    collisionManager.RegisterObject("Food", food);

    collisionManager.RegisterCollisionCallback("Player", "Food", [&]() {
        std::cout << "Nom nom!" << std::endl;
        collisionManager.ClearOneObjectAndCallback(food);
        Food::DeleteFood(food);
        food = nullptr;
        spawnManager.setFoodCurrentlySpawned(false);

        // Add to player's tail?

    });
}

void runSnakeGame() {
    // Setup window
    sf::RenderWindow window(sf::VideoMode({800,600}), "SFML Test", sf::Style::Titlebar);

    // Spawn player
    MoveableObject player = Player::SpawnPlayer("img/sword32.png", {0,0}, 0.05f);

    // Spawning system
    SpawnManager spawnManager;
    Food* food = nullptr;

    // Collisions
    CollisionManager collisionManager;

    while (window.isOpen()) {
        // Check for events
        CheckForWindowEvents(window);
        ConstantlyMovePlayer(player, window);
        CheckForDirectionChanges(player);

        // Boundary and collision stuff
        collisionManager.CheckCollisions();

        // Food spawning
        if (!spawnManager.getFoodCurrentlySpawned()) {
            food = spawnManager.spawnFoodInRandomLocation(window);

            if (food != nullptr) {
                SetupCollisions(spawnManager, collisionManager, player, food);
                spawnManager.setFoodCurrentlySpawned(true);
            }
        }

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