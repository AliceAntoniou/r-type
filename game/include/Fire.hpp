/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** fire
*/

#pragma once

#include "Systems.hpp"
#include "UwUgine.hpp"

namespace game
{
    namespace Component
    {
        /**
         * @brief Class Fire
         */
        class Fire {
            public:
                /**
                 * @Fire default contructor
                 */
                Fire() = default;
                /**
                 * @brief Fire constructor :
                 * @brief add constructor and its components to the registery
                 */
                Fire(uwugine::Registery &r, uwugine::Point2f pos, float angle, const std::string target);
                /**
                 * @brief Fire default copy constructor
                 */
                Fire(Fire const &) = default;
                /**
                 * @brief Fire default copy constructor
                 */
                Fire(Fire &&) noexcept = default;
                /**
                 * @brief Fire default destructor
                 */
                ~Fire(void) = default;
                /**
                 * @brief Fire operator =
                 */
                Fire &operator=(Fire const &) = default;
                /**
                 * @brief Fire operator =
                 */
                Fire &operator=(Fire &&) noexcept = default;
                /**
                 * @brief Destroy Fire entity
                 */
                void delete_component(uwugine::Registery &);
                /**
                 * @brief get sheet frames of the Fire
                 *
                 * @return std::vector<uwugine::Point2u>
                 */
                std::vector<uwugine::Point2u> getSheetFrames(void);
                /**
                 * @brief id of Fire entity
                 */
                uwugine::entity_t id;
                int power = 1;

            private:
                std::string target;
        };
    }
}