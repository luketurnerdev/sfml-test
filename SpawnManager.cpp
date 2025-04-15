//
// Created by luke on 15/04/2025.
//

#include "SpawnManager.h"

#include "Food.h"
#include "Utils.h"

SpawnManager::SpawnManager() {
    foodIsCurrentlySpawned_ = false;
}

Food* SpawnManager::spawnFoodInRandomLocation(const sf::RenderWindow& window) {
    if (foodIsCurrentlySpawned_) {return nullptr;}
    // Use the dimensions of the window as boundaries
    // TODO take in the size of the food as well (dont spawn halfway into wall)
    float xPos = static_cast<float>(RandomNumber(0,window.getSize().x));
    float yPos = static_cast<float>(RandomNumber(0,window.getSize().y));

    // TODO - make the next 3 lines dynamic (default texture, random location)
    sf::Texture foodTexture;
    foodTexture.loadFromFile("img/banana32.png");

    // Spawn it
    Food* food = Food::SpawnFood(foodTexture, {xPos,yPos});
    setFoodCurrentlySpawned(true);
    return food;
};

void SpawnManager::setLastSpawnLocation(const Position newPos) {
    lastSpawnLocation_ = newPos;
};

const Position& SpawnManager::getLastSpawnLocation() const {
    return lastSpawnLocation_;
}

bool SpawnManager::getFoodCurrentlySpawned() const {
    return foodIsCurrentlySpawned_;
}

void SpawnManager::setFoodCurrentlySpawned(bool isSpawned) {
    foodIsCurrentlySpawned_ = isSpawned;
}