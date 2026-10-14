#include <SFML/Graphics.hpp>
#include <iostream>

#include "game_system.hpp"
#include "game_parameters.hpp"
#include "bullet.hpp"

sf::Texture GameSystem::spritesheet;
std::vector<std::shared_ptr<Ship>> GameSystem::ships;

void GameSystem::init() {
    if (!spritesheet.loadFromFile("resources/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }
    reset();
}

void GameSystem::reset() {
    clean();
    Bullet::init();

    Invader::direction = true;
    Invader::speed = Parameters::invader_speed;
    Invader::acc = Parameters::invader_acc;

    std::shared_ptr<Player> player = std::make_shared<Player>();
    ships.push_back(player);

    for (int i = 0; i < Parameters::rows; i++) {
        const sf::IntRect sprite_rect(
            sf::Vector2i(i/2 * 2 * Parameters::sprite_size, 0),
            sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size)
        );
        for (int j = 0; j < Parameters::columns; j++) {
            const float x = static_cast<float>(Parameters::invader_space_left) + static_cast<float>(j) * static_cast<float>(Parameters::invader_spacing_x);
            const float y = static_cast<float>(Parameters::invader_space_top) + static_cast<float>(i) * static_cast<float>(Parameters::invader_spacing_y);
            std::shared_ptr<Invader> inv = std::make_shared<Invader>(sprite_rect, sf::Vector2f(x, y));
            ships.push_back(inv);
        }
    }
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
    Bullet::update(dt);

    if (ships[0] -> is_exploded()) {
        reset();
    }
}

void GameSystem::render(sf::RenderWindow &window) {
    for (const std::shared_ptr<Ship> &s : ships) {
        window.draw(*(s.get()));
    }
    Bullet::render(window);
}