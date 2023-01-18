/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Object
*/

#pragma once

#include "Registery.hpp"

namespace uwugine
{
    template <class... Class> class Object {
        public:
            Object(void) noexcept = delete;
            /**
             * @brief Construct a new Object
             *
             * @param r Rgistery
             * @param componants All the component required
             */
            Object(Registery &r, Class &&...componants) : registery(r), id(r.spawn_entity())
            {
                (r.add_component<Class>(id, std::move(componants)), ...);
            }
            Object(const Object &) noexcept = default;
            Object(Object &&) noexcept = default;
            ~Object(void) noexcept = default;

            Object &operator=(const Object &) noexcept = default;
            Object &operator=(Object &&) noexcept = default;

            /**
             * @brief Get the Entity_t
             *
             * @return const entity_t&
             */
            const entity_t &getId(void) const { return id; }
            /**
             * @brief Get the Component of this Object
             *
             * @tparam Component
             * @return Component&
             */
            template <typename Component> Component &getComponent(void) { return registery.get_components<Component>()[id]; }

        protected:
            Registery &registery;
            entity_t id;
    };
} // namespace uwugine