#include <SFML/Graphics.hpp>
#include <iostream>

#include "game_system.hpp"
#include "game_parameters.hpp"

sf::Texture GameSystem::spritesheet;
sf::Sprite GameSystem::invader;

void GameSystem::init() {
    if (!spritesheet.loadFromFile("resources/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size)));
}

void GameSystem::clean() {}

void GameSystem::update(const float &dt) {}

void GameSystem::render(sf::RenderWindow &window) {
    window.draw(invader);
}