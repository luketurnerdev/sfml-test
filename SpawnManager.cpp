//
// Created by luke on 15/04/2025.
//

#include "SpawnManager.h"

#include "Food.h"

SpawnManager::SpawnManager() {
    foodIsCurrentlySpawned_ = false;
}

void SpawnManager::spawnFoodInRandomLocation(Position spawnPos) {
    if (foodIsCurrentlySpawned_) return;

    // TODO - make the next 3 lines dynamic (default texture, random location)
    sf::Texture foodTexture;
    foodTexture.loadFromFile("img/banana32.png");
    Food::SpawnFood(foodTexture, {100,100});
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