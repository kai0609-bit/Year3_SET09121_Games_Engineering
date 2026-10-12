#include <SFML/Graphics.hpp>
#include <iostream>

#include "game_parameters.hpp"

// Objects of the game
sf::Texture spritesheet;
sf::Sprite invader;

void init() {
    if (!spritesheet.loadFromFile("resources/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size)));
}

void render(sf::RenderWindow &window) {
    window.draw(invader);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(Parameters::game_width, Parameters::game_height), "Space-Invaders");
    init();
    sf::Clock clock;
    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        window.clear();
        render(window);
        window.display();
    }
    return 0;
}