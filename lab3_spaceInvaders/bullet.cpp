#include "bullet.hpp"
#include "game_system.hpp"
#include "game_parameters.hpp"

unsigned char Bullet::_bulletPointer;
Bullet Bullet::_bullets[256];

Bullet::Bullet() {}

void Bullet::update(const float &dt) {
    for(int i = 0; i < 256; i++)
        _bullets[i]._update(dt);
}

void Bullet::render(sf::RenderWindow &window) {
    for(int i = 0; i < 256; i++) {
        window.draw(_bullets[i]);
    }
}

void Bullet::fire(const sf::Vector2f &pos, const bool mode) {
    Bullet &bullet = _bullets[++_bulletPointer];
    if(mode) 
        bullet.setTextureRect(sf::IntRect(sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size), sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size)));
    else 
        bullet.setTextureRect(sf::IntRect(sf::Vector2i(Parameters::sprite_size*2, Parameters::sprite_size), sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size)));
    
    bullet.setPosition(pos);
    bullet._mode = mode;
}

void Bullet::init() {
    for (int i = 0; i < 256; i++) {
        _bullets[i].setTexture(GameSystem::spritesheet);
        _bullets[i].setOrigin(Parameters::sprite_size/2.f, Parameters::sprite_size/2.f);
        _bullets[i].setPosition(-100, -100);
    }
}

void Bullet::_update(const float &dt) {
    if (getPosition().y < -Parameters::sprite_size || getPosition().y > Parameters::game_height + Parameters::sprite_size) {
        //off screen - do nothing
        return;
    } else {
        move(sf::Vector2f(0, dt * Parameters::bullet_speed * (_mode ? -1.0f : 1.0f)));
        const sf::FloatRect bounding_box = getGlobalBounds();
        std::shared_ptr<Ship> &player = GameSystem::ships[0];
        for (std::shared_ptr<Ship> &s : GameSystem::ships) {
            if (_mode && s == player) {
                //player bullets don't collide with player
                continue;
            }
            if (!_mode && s != player) {
                //invader bullets don't collide with other invaders
                continue;
            }
            if (!s->is_exploded() && 
                s->getGlobalBounds().intersects(bounding_box)) {
                  //Explode the ship
                  s->explode();
                  //warp bullet off-screen
				  setPosition(sf::Vector2f(-100, -100));
                  return;
            }
        }
    }
}
