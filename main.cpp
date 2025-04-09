#include <SFML/Graphics.hpp>
void CheckForWindowEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void MoveBasedOnKeyPresses(float& xPos, float& yPos, const float& movementIncrement) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        xPos += movementIncrement;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        xPos -= movementIncrement;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        yPos += movementIncrement;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        yPos -= movementIncrement;
    }
}

void MoveSpriteAndDrawToScreen(sf::Sprite& sprite, float& xPos, float& yPos, sf::RenderWindow& window ) {
    sprite.setPosition({xPos, yPos});
    window.draw(sprite);
}

void SetInitialSpritePos(sf::Sprite& sprite, const float& startingXPos, const float& startingYPos) {
    const sf::Vector2f startingPos = {startingXPos, startingYPos};
    sprite.setPosition(startingPos);
}

int main() {

    // Globals
    sf::RenderWindow window(sf::VideoMode({800,600}), "SFML Test", sf::Style::Titlebar);

    // Positioning and movement
    float characterXPos = 0;
    float characterYPos = 0;

    float secondXPos = 100;
    float secondYPos = 100;

    float movementIncrement = 0.05f;

    // Textures, sprites
    const sf::Texture characterTexture("img/sword32.png");
    const sf::Texture secondTexture("img/sword32.png");

    sf::Sprite characterSprite(characterTexture);
    sf::Sprite secondSprite(secondTexture);

    // Initial positions on screen
    SetInitialSpritePos(characterSprite, characterXPos, characterYPos);
    SetInitialSpritePos(secondSprite, secondXPos, secondYPos);

    while (window.isOpen()) {
        // Check for events
        CheckForWindowEvents(window);
        MoveBasedOnKeyPresses(characterXPos, characterYPos, movementIncrement);
        MoveBasedOnKeyPresses(secondXPos, secondYPos, movementIncrement );

        // Drawing to the screen

        // Clear anything previously drawn
        window.clear(sf::Color::Black);

        // Sprite movement
        MoveSpriteAndDrawToScreen(characterSprite, characterXPos, characterYPos, window);
        MoveSpriteAndDrawToScreen(secondSprite, secondXPos, secondYPos, window );

        // Display the current frame with what was drawn
        window.display();
    }
    return 0;
}
