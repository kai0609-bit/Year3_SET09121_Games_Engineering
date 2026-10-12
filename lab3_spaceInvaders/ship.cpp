#include "ship.hpp"
#include "game_system.hpp"

Ship::Ship() {}

Ship::Ship(const Ship &s) :
    Sprite(s),
    _sprite(s._sprite){}

Ship::Ship(sf::IntRect ir) : Sprite() {
    _sprite = ir;
    setTexture(GameSystem::spritesheet);
    setTextureRect(_sprite);
}

void Ship::update(const float &dt) {}

// Define the ship deconstructor
// Although we set this pure virtual, we still have to define it
Ship::~Ship() = default;