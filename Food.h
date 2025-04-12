//
// Created by luke on 9/04/2025.
//

#ifndef FOOD_H
#define FOOD_H
#include "MoveableObject.h"

/*
 * Food inherits from MoveableObject, in the sense that its spawnPosition can be determined, but the player cannot move it.
 * Food also needs the ability to be eaten, which requires:
 * -> Collision detection: if the player runs into it, a trigger should be detected, which:
 * ---> deletes the instance of food
 * ---> adds to the player score
 * ---> adds to the tail of the player
 *
*/
class Food : public MoveableObject {
public:
    Food(const sf::Texture& texture, const Position& spawnPos);
    static Food SpawnFood(const std::string& texturePath, Position spawnPosition);
};
#endif //FOOD_H
