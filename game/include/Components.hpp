/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Components_Types
*/

#pragma once

#include "Background.hpp"
#include "EnemyWaves.hpp"
#include "Fire.hpp"
#include "UwUgine.hpp"

#include <cstddef>
#include <map>
namespace game
{
    /**
     * Namespace containing all entity from the game
     */
    namespace Component
    {
        /**
         * @brief Class Amob :
         * @brief generic mob class
         */
        class AMob {
            public:
                AMob(void) = default;

                AMob(AMob const &) = default;
                AMob(AMob &&) noexcept = default;
                ~AMob(void) = default;

                AMob &operator=(AMob const &) = default;
                AMob &operator=(AMob &&) noexcept = default;

                virtual void move(uwugine::Registery &r) = 0;
                virtual void fire(uwugine::Registery &r) = 0;
                /**
                 * @brief Updates mob damages
                 *
                 * @param r
                 * @param damages
                 */
                void get_damages(uwugine::Registery &r, int damages);
                /**
                 * @brief Destroy Mob entity
                 */
                void delete_component(uwugine::Registery &);
                /**
                 * id of Mob entity
                 */
                uwugine::entity_t id;

            protected:
                int PV = 3;
                int power = 1;
        };

        /**
         * @brief Class Enemy
         */
        class Enemy : public AMob {
            public:
                /**
                 * @brief Enemy default constructor :
                 * @brief Takes an Enemy
                 */
                Enemy(void) = default;
                /**
                 * @brief Enemy default copy constructor :
                 */
                Enemy(Enemy const &) = default;
                /**
                 * @brief Enemy default copy constructor :
                 */
                Enemy(Enemy &&) noexcept = default;
                /**
                 * Enemy default destructor
                 */
                ~Enemy(void) = default;
                /**
                 * @brief Enemy operator =
                 */
                Enemy &operator=(Enemy const &) = default;
                /**
                 * @brief Enemy operator =
                 */
                Enemy &operator=(Enemy &&) noexcept = default;
                /**
                 * @brief Update Enemy position
                 */
                void move(uwugine::Registery &r) final;
                /**
                 * @brief Create Fire entity from Enemy position
                 */
                void fire(uwugine::Registery &r) final;
                /**
                 * @brief Create enemy :
                 * @brief add enemy's components to the registery
                 */
                void create(uwugine::Registery &r, struct EnemyProperties properties);

            private:
                std::map<std::string, int> settings_i{
                    {"x", 0}, {"y", 1}, {"file_name", 2}, {"size_frame_x", 3}, {"size_frame_y", 4}, {"nb_frames", 5}, {"PV", 6}};
        };

        /**
         * @brief Class Player
         */
        class Player : public AMob {
            public:
                /**
                 * @brief Player default contructor
                 */
                Player(void) = default;
                /**
                 * @brief Player constructor :
                 * @brief add Player's components to the registery
                 */
                Player(uwugine::Registery &r, uwugine::Point2f pos);
                /**
                 * @brief Player default copy constructor
                 */
                Player(Player const &) = default;
                /**
                 * @brief Player default copy constructor
                 */
                Player(Player &&) noexcept = default;
                /**
                 * @brief Player default destructor
                 */
                ~Player(void) = default;
                /**
                 * @brief Player operator =
                 */
                Player &operator=(Player const &) = default;
                /**
                 * @brief Player operator =
                 */
                Player &operator=(Player &&) noexcept = default;
                /**
                 * @brief Update Player position
                 */
                void move(uwugine::Registery &r) final;
                /**
                 * @brief Create Fire entity from Player position
                 */
                void fire(uwugine::Registery &r) final;
                bool is_colliding = false;

            private:
                std::map<int, float> levels = {};
                int level = 0;
        };
    };
};
