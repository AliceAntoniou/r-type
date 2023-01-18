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

struct ObstaclesProperties {
        std::string name; // useless unless we decide to implement name tags (for bosses)
        int id;
        int speed;
        int spawn_time;     // relative to the wave
        int spawn_position; // percentage of the height of the window
        std::string sprite_path;
        std::pair<int, int> sprite_size;
        int sprite_nb_frames;
        int x;
        int y;
        float scale;
};

struct Map {
        std::string map_name;
        int map_id;                                     // wave apparition order
        unsigned int obstacles_qty;                     // number of obstacles in the wave
        std::vector<ObstaclesProperties> map_obstacles; // obstacles in the wave
};
