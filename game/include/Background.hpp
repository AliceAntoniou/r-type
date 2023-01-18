/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** background
*/

#pragma once

#include "UwUgine.hpp"
#include <math.h>

namespace game
{
    namespace Component
    {
        /**
         * Class Background
         */
        class Background {
            public:
                /**
                 * @brief Background constructor
                 */
                Background() = default;
                /**
                 * @brief Background constructor :
                 * @brief add all Background's components to the registery
                 */
                Background(uwugine::Registery &r);
                /**
                 * @brief Background copy constructor
                 */
                Background(Background const &) = default;
                /**
                 * @brief Background copy constructor
                 */
                Background(Background &&) noexcept = default;
                /**
                 * @brief Background default destructor
                 */
                ~Background(void) = default;
                /**
                 * @brief Background operator =
                 */
                Background &operator=(Background const &) = default;
                /**
                 * @brief Background operator =
                 */
                Background &operator=(Background &&) noexcept = default;
                /**
                 * @brief Destroy Background entity
                 */
                void delete_component(uwugine::Registery &);
                /**
                 * @brief get sheet frames of the background
                 *
                 * @return std::vector<uwugine::Point2u>
                 */
                std::vector<uwugine::Point2u> getSheetFrames(void);
                /**
                 * @brief id of Background entity
                 */
                uwugine::entity_t id;
        };
    };
};
