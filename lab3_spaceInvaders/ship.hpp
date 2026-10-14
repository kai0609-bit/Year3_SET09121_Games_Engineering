#pragma once

#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
public:
    Ship();
    // Copy constructor
    Ship(const Ship &s);
    // Constructor that takes a sprite
    Ship(sf::IntRect ir);
    // Pure virtual deconstructor -- makes this an abstract class and avoids undefined behabiour
    virtual ~Ship() = 0;
    // Update, virtual so can be overriden, but not pure virtual 
    virtual void update(const float &dt);

    virtual void move_down();

    bool is_exploded() const;

    virtual void explode();
protected:
    sf::IntRect _sprite;
    bool _exploded = false;
};

class Invader : public Ship {
public:
    static bool direction;
    static float speed;
    static float acc;
    Invader();
    Invader(const Invader& inv);
    Invader(sf::IntRect ir, sf::Vector2f pos);
    void update(const float &dt) override;
    void move_down() override;
    void explode() override;
protected:
    float _firetime = 0.f;
    float _explode_timer = 0.f;
};

class Player : public Ship {
public:
    Player();
    void update(const float &dt) override;
protected:
    static float _firetime;
};