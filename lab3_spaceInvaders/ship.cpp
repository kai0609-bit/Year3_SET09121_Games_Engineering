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
void Ship::move_down() {}

// Define the ship deconstructor
// Although we set this pure virtual, we still have to define it
Ship::~Ship() = default;

bool Invader::direction;
float Invader::speed;
float Invader::acc;

Invader::Invader() : Ship() {}
Invader::Invader(const Invader &inv): Ship(inv) {}
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(sf::Vector2f(Parameters::sprite_size / 2.f, Parameters::sprite_size / 2.f));
    setPosition(pos);
}

void Invader::update(const float &dt) {
    Ship::update(dt);

    move(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f);

    if ((direction && getPosition().x > Parameters::game_width - Parameters::sprite_size/2.f) || 
        (!direction && getPosition().x < Parameters::sprite_size/2.f)) {
            direction = !direction;
            speed += Invader::acc;
            for (std::shared_ptr<Ship> &ship: GameSystem::ships) {
					 ship->move_down();
            }
        }
}

void Invader::move_down() {
    move(0.f, Parameters::invader_move_down);
}