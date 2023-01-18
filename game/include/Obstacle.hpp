/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Components_Types
*/

#pragma once

#include "UwUgine.hpp"
#include "Map.hpp"

namespace game
{
    /**
    * @brief Component Class
    */
    namespace Component
    {
        class Obstacle {
                public :
                        /**
                        * @brief Obstacle default contructor
                        */
                        Obstacle() = default;
                        /**
                        * @brief Obstacle default copy constructor
                        */
                        Obstacle(Obstacle const &) = default;
                        /**
                        * @brief Obstacle default copy constructor
                        */
                        Obstacle(Obstacle &&) noexcept = default;
                        /**
                        * @brief Obstacle default destructor
                        */
                        ~Obstacle(void) = default;
                        /**
                        * @brief Obstacle operator =
                        */
                        Obstacle &operator=(Obstacle const &) = default;
                        /**
                        * @brief Obstacle operator =
                        */
                        Obstacle &operator=(Obstacle &&) noexcept = default;
                        /**
                        * @brief Destroy Obstacle entity
                        */
                        void delete_component(uwugine::Registery &);
                        /**
                        * @brief Create Obstacle : 
                        * @brief add obstacle's components to the registery
                        */
                        void create(uwugine::Registery &r, struct ObstaclesProperties properties);
                        /**
                        * id of Obstacle entity
                        */
                        uwugine::entity_t id;
                    private :
                        std::map<std::string, int> settings_i {
                                {"x", 0},
                                {"y", 1},
                                {"file_name", 2},
                                {"size_frame_x", 3},
                                {"size_frame_y", 4},
                                {"nb_frames", 5},
                        };
        };
    };
};
