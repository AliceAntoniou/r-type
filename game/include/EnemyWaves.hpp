//
// Created by natan on 05/11/2022.
//

#ifndef RTYPE_ENEMYWAVES_HPP
    #define RTYPE_ENEMYWAVES_HPP

#endif // RTYPE_ENEMYWAVES_HPP

#pragma once
#include "Components.hpp"
#include <string>
#include <vector>

struct EnemyProperties {
        std::string enemy_name; // useless unless we decide to implement name tags (for bosses)
        int id;
        int health;
        int damage;
        int speed;
        int spawn_time;                     // relative to the wave
        std::pair<int, int> spawn_position; // x, y
        std::string sprite_path;
        std::pair<int, int> sprite_size;
        int sprite_nb_frames;
};

struct EnemyWave {
        std::string wave_name;
        int wave_id;                               // wave apparition order
        int wave_duration;                         // wave duration in seconds
        int difficulty_index;                      // difficulty index (between 0 and 100)
        unsigned int enemy_qty;                    // number of enemies in the wave
        std::vector<EnemyProperties> wave_enemies; // enemies in the wave
};
