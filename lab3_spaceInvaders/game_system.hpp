#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "ship.hpp"

struct GameSystem {
    // The global variables
    static std::vector<std::shared_ptr<Ship>> ships;
    static sf::Texture spritesheet;

    // game system function
    static void init();
    static void reset();
    static void clean();
    static void update(const float &dt);
    static void render(sf::RenderWindow &window);
};