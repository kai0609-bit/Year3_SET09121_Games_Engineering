#include <SFML/Graphics.hpp>
#include <iostream>

#include "game_system.hpp"
#include "game_parameters.hpp"

sf::Texture GameSystem::spritesheet;
std::vector<std::shared_ptr<Ship>> GameSystem::ships;

void GameSystem::init() {
    if (!spritesheet.loadFromFile("resources/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }

    std::shared_ptr<Invader> inv = std::make_shared<Invader>(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size)), sf::Vector2f(100.f, 100.f));
    ships.push_back(inv);
}

void GameSystem::clean() {
    for (std::shared_ptr<Ship> &ship: ships) {
        ship.reset();
    }
    ships.clear();
}

void GameSystem::update(const float &dt) {
    for (std::shared_ptr<Ship> &s : ships) {
        s->update(dt);
    }
}

void GameSystem::render(sf::RenderWindow &window) {
    for (const std::shared_ptr<Ship> &s : ships) {
        window.draw(*(s.get()));
    }
}