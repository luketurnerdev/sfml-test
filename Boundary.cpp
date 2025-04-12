//
// Created by luke on 12/04/2025.
//

#include "Boundary.h"
#include <SFML/Graphics.hpp>

#include "MoveableObject.h"

sf::VertexArray CreateBoundarySquare(const Boundary& boundaryToDraw) {

 sf::VertexArray square(sf::PrimitiveType::LineStrip, 5);
    square[0].position = sf::Vector2f(boundaryToDraw.topLeftCorner.x, boundaryToDraw.topLeftCorner.y);   // Top-left
    square[1].position = sf::Vector2f(boundaryToDraw.topRightCorner.x, boundaryToDraw.topRightCorner.y);   // Top-right
    square[2].position = sf::Vector2f(boundaryToDraw.bottomRightCorner.x, boundaryToDraw.bottomRightCorner.y);   // Bottom-right
    square[3].position = sf::Vector2f(boundaryToDraw.bottomLeftCorner.x, boundaryToDraw.bottomLeftCorner.y);   // Bottom-left
    square[4].position = sf::Vector2f(boundaryToDraw.topLeftCorner.x, boundaryToDraw.topLeftCorner.y);    // Back to Top-left
    return square;
}

void DrawBoundarySquareOnScreenThisFrame(const MoveableObject& object, sf::RenderWindow& window) {
    const sf::VertexArray square = CreateBoundarySquare(object.getBoundary());
    window.draw(square);
}

