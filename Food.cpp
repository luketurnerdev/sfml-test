//
// Created by luke on 9/04/2025.
//

#include "Food.h"

Food::Food(const sf::Texture& texture, const Position& spawnPos) : MoveableObject(texture, spawnPos){}

Food* Food::SpawnFood(const sf::Texture& texture, Position spawnPosition) {
    // Allocate the memory on the heap
    Food* food = new Food(texture, spawnPosition);

    // Set a static boundary for the food for collisions
    food->setBoundary();
    return food;
}

void Food::DeleteFood(Food*& foodInstance) {
    // we need to delete the food from memory, including stopping the rendering of its texture
    // Free the previously allocated memory
    delete foodInstance;

    // Clear the pointer so we don't point to something that doesn't exist
    foodInstance = nullptr;
}

