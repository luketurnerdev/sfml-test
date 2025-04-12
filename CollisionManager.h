//
// Created by luke on 12/04/2025.
//

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "Boundary.h"
#include "MoveableObject.h"

struct PairHash {
    std::size_t operator()(const std::pair<std::string, std::string>& pair) const {
        return std::hash<std::string>()(pair.first) ^ std::hash<std::string>()(pair.second);
    }
};

class CollisionManager {
public:
    CollisionManager();
    // Take the MoveableObject in memory and register it as a new Tag
    void RegisterObject(const std::string& tag, MoveableObject* object);

    // Removes all registered objects and callbacks
    void Clear();

    // Setup tagA to have a collision interaction with tagB, and fire a callback
    void RegisterCollisionCallback(const std::string tagA, const std::string tagB, std::function<void()> callback);

    // Will run every frame, checks all collision interactions if they happened this frame
    void CheckCollisions();

private:

    // Properties of the object to be setup for collisions
    struct RegisteredObject {
        std::string tag;
        MoveableObject* object;
    };

    // List of all registered objects
    std::vector<RegisteredObject> objects;

    // A list of all registered callbacks and their associated tag pairs
    std::unordered_map<
        std::pair<std::string, std::string>,
        std::function<void()>,
        PairHash
    > callbacks;

    // Helper to check for overlaps
    static bool IsOverlapping(const Boundary& a, const Boundary& b);

    // Creates a sorted key from two tags to ensure cross-compatibility of string pairs
    static std::pair<std::string, std::string> MakeSortedKey(const std::string& a, const std::string& b);
};

#endif //COLLISIONMANAGER_H
