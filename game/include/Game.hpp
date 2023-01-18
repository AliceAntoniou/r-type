/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** game
*/

#pragma once

#include "UwUgine.hpp"

namespace game
{
    /**
     * @brief Class Game
     */
    class Game {
        public:
            /**
             * @brief Game default constructor
             */
            Game() = default;
            /**
             * @brief Game default destructor
             */
            ~Game() noexcept = default;
            /**
             * @brief Launch game
             */
            void launch_game();
            /**
             * @brief Add waves system to the game
             */
            void add_waves_system();
            /**
             * @brief Add all systems needed by the game
             */
            void add_game_systems();
            /**
             * @brief Add an enemy to the game
             */
            void add_enemy();
            /**
             * @brief Add the map of the game
             */
            void add_map();
            /**
             * @brief Replace current registery used by the Game
             */
            void set_registery(uwugine::Registery &new_r);

        protected:

        private:
            uwugine::Clock clock;
            uwugine::Registery r;
    };
};
