#pragma once

struct Parameters {
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr int sprite_size = 32;
    static constexpr int rows = 5;
    static constexpr int columns = 12;
    static constexpr int invader_spacing_x = 48;
    static constexpr int invader_spacing_y = 40;
    static constexpr int invader_space_left = 100;
    static constexpr int invader_space_top = 50;
    static constexpr float invader_speed = 20.f;
    static constexpr float invader_acc = 5.f;
    static constexpr float invader_kill_acc = 3.f;
    static constexpr float invader_fire_cooldown = 3.f;
    static constexpr int invader_fire_random = 60;
    static constexpr float invader_fade_time = 1.f;
    static constexpr float invader_move_down = 24.f;  
    static constexpr float player_speed = 200.f;
    static constexpr float bullet_speed = 200.f;
    static constexpr float cooldown_time = 0.7f;
};