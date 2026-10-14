#include "ship.hpp"
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "bullet.hpp"

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

void Ship::explode() {
    setTextureRect(sf::IntRect(sf::Vector2i(Parameters::sprite_size * 4, Parameters::sprite_size), sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size)));
    _exploded = true;
}

// Define the ship deconstructor
// Although we set this pure virtual, we still have to define it
Ship::~Ship() = default;

bool Ship::is_exploded() const {
  return _exploded;
}

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

Player::Player() : 
Ship(sf::IntRect(sf::Vector2i(Parameters::sprite_size*5, Parameters::sprite_size), sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size))) {
    setOrigin(Parameters::sprite_size/2.f, Parameters::sprite_size/2.f);
    setPosition(Parameters::game_width/2.f, Parameters::game_height - static_cast<float>(Parameters::sprite_size));
}

float Player::_firetime = 0;

void Player::update(const float &dt) {
    Ship::update(dt);

    _firetime -= dt;

    float player_direction = 0.f;
    // Move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player_direction --;
    }

    // Move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player_direction ++;
    }

    move(player_direction * dt * Parameters::player_speed, 0.f);

    const float half_width = Parameters::sprite_size / 2.f;
    const float min_x = half_width;
    const float max_x = Parameters::game_width - half_width;
    if (getPosition().x < min_x) {
        setPosition(min_x, getPosition().y);
    } else if (getPosition().x > max_x) {
        setPosition(max_x, getPosition().y);
    }

    // Fire bullet
    if (_firetime <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        Bullet::fire(getPosition(), true);
        _firetime = Parameters::cooldown_time;
    }
}


