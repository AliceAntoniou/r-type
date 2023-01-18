/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** systems
*/

#pragma once

#include "Components.hpp"
#include "UwUgine.hpp"
#include <iostream>
#include <math.h>
#include <sstream>

namespace game
{
    namespace Systems
    {
        /**
         * @brief Handle the enemy waves
         */
        void waves_system(uwugine::Registery &r);
        /**
         * @brief Update the state of the mobs in the registery
         */
        void update_mobs(uwugine::Registery &r);
        /**
         * @brief used in case of collision between two hitboxes
         */
        void fireBall_collisions(uwugine::Registery &r, const std::string &me, const std::string &other);
    };
};
