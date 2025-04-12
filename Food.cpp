//
// Created by luke on 9/04/2025.
//

#include "Food.h"

Food::Food(const sf::Texture& texture, const Position& spawnPos) : MoveableObject(texture, spawnPos){}

Food Food::SpawnFood(const std::string& texturePath, Position spawnPosition) {
    // Init food (sample)
    const sf::Texture foodTexture(texturePath);
    Food food(foodTexture, spawnPosition);

    // Set a static boundary for the food for collisions
    food.setBoundary();
    return food;
}
