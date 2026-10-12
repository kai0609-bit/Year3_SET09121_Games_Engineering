#include "ship.hpp"
#include "game_system.hpp"
#include "game_parameters.hpp"

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

Invader::Invader() : Ship() {}
Invader::Invader(const Invader &inv): Ship(inv) {}
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(sf::Vector2f(Parameters::sprite_size / 2.f, Parameters::sprite_size / 2.f));
    setPosition(pos);
}

void Invader::update(const float &dt) {
    Ship::update(dt);
}