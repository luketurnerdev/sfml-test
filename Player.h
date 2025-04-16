//
// Created by luke on 12/04/2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "MoveableObject.h"
#include "Position.h"
#include <SFML/Graphics.hpp>

class Player {
public:
    static MoveableObject SpawnPlayer(const std::string& texturePath, const Position spawnPosition, const float playerMovementIncrement);
};

#endif //PLAYER_H
