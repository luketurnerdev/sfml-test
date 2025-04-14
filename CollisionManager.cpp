//
// Created by luke on 12/04/2025.
//

#include "CollisionManager.h"
#include <functional>
#include <utility>
#include "MoveableObject.h"

CollisionManager::CollisionManager() = default;

void CollisionManager::RegisterObject(const std::string &tag, MoveableObject *object) {
    // add to the objects array
    objects.push_back({tag, object});
}

void CollisionManager::ClearAllCollisionObjectsAndCallbacks() {
    objects.clear();
    callbacks.clear();
}

void CollisionManager::ClearOneObjectAndCallback(MoveableObject* objectToClear) {
    std::string tagToRemove;

    // Remove from objects list
    objects.erase(
        std::remove_if(objects.begin(), objects.end(), [&](const RegisteredObject obj) {
            if (obj.object == objectToClear) {
                tagToRemove = obj.tag;
                return true;
            }
            return false;
    }),
    objects.end()
    );

    // Remove all callbacks that this tag is used in

    for (auto it = callbacks.begin(); it != callbacks.end();) {
        const auto& key = it->first;

        if (key.first == tagToRemove || key.second == tagToRemove) {
            it = callbacks.erase(it);
        } else {
            ++it;
        }
    }
}


void CollisionManager::RegisterCollisionCallback(const std::string tagA, const std::string tagB, std::function<void()> callback) {
    auto key = MakeSortedKey(tagA, tagB);
    callbacks[key] = callback;
}

bool CollisionManager::IsOverlapping(const Boundary &a, const Boundary &b) {
    const float aLeft = a.topLeftCorner.x; // 0
    const float aRight = a.topRightCorner.x; // 10
    const float aTop = a.topLeftCorner.y; // 0
    const float aBottom = a.bottomLeftCorner.y; // 10

    const float bLeft = b.topLeftCorner.x;
    const float bRight = b.topRightCorner.x;
    const float bTop = b.topLeftCorner.y;
    const float bBottom = b.bottomLeftCorner.y;

    return !(aRight < bLeft ||
             aLeft > bRight ||
             aBottom < bTop ||
             aTop > bBottom);
}

void CollisionManager::CheckCollisions() {
    // Loop through all the objects we have registered
    for (size_t i = 0; i < objects.size(); i++) {
        // Only include valid pairs (eg no repeats or invalid pairings)
        // E.g., A-B is valid, but B-A should be skipped, as should A-A.
        // For the second tag, we
        for (size_t j = i + 1; j < objects.size(); ++j) {

            const auto& objA = objects[i];
            const auto& objB = objects[j];

            if (objA.object == nullptr || objB.object == nullptr) {
                continue;
            }

            if (IsOverlapping(objA.object->getBoundary(), objB.object->getBoundary())) {
                auto key = MakeSortedKey(objA.tag, objB.tag);

                if (auto it = callbacks.find(key); it != callbacks.end()) {
                    it->second(); // Call it
                }
            }
        }
    }
}

std::pair<std::string, std::string> CollisionManager::MakeSortedKey(const std::string& a, const std::string& b) {
    if (a < b) return {a, b};
    else       return {b, a};
}






