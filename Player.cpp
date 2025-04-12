//
// Created by luke on 12/04/2025.
//

#include "Player.h"
#include "MoveableObject.h"

MoveableObject Player::SpawnPlayer(const std::string& texturePath, const Position spawnPosition, const float playerMovementIncrement) {
    const sf::Texture characterTexture(texturePath);
    MoveableObject player(characterTexture, spawnPosition, playerMovementIncrement);

    return player;
}