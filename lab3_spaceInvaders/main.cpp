#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "game_parameters.hpp"
#include "game_system.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(Parameters::game_width, Parameters::game_height), "Space-Invaders");
    GameSystem::init();
    sf::Clock clock;
    srand(static_cast<unsigned>(time(nullptr)));
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

        GameSystem::update(dt);
        window.clear();
        GameSystem::render(window);
        window.display();
    }
    GameSystem::clean();
    return 0;
}