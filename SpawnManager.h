//
// Created by luke on 15/04/2025.
//

#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H
#include "Food.h"
#include "Position.h"
/*
    We will need:
    - A method to spawn new food objects in random locations - calls Food::SpawnFood
    - A list of currently spawned foods?
    - a record of the most recent location so we avoid it next time
*/

class SpawnManager {
public:
    SpawnManager();
    Food* spawnFoodInRandomLocation();
    void setLastSpawnLocation(const Position newPos);
    void setFoodCurrentlySpawned(bool isSpawned);

    bool getFoodCurrentlySpawned() const;
    const Position& getLastSpawnLocation() const;
private:
    bool foodIsCurrentlySpawned_;
    Position lastSpawnLocation_ = {0,0};
};
#endif //SPAWNMANAGER_H
