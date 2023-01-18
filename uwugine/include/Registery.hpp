/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Registery
*/

#pragma once

#include "Bindings.hpp"
#include "Client.hpp"
#include "Container.hpp"
#include "Exception.hpp"
#include "Window.hpp"
#include <any>
#include <typeindex>
#include <unordered_map>

namespace uwugine
{
    typedef std::size_t entity_t;
    class Registery {
        public:
            using system_t = void (*)(Registery &);

            Registery(void);
            Registery(const Point2u &size, const std::string &title);

            Registery(const Registery &) noexcept = delete;
            Registery(Registery &&) noexcept = delete;
            ~Registery(void) noexcept = default;

            Registery &operator=(const Registery &) noexcept = delete;
            Registery &operator=(Registery &&) noexcept = delete;

            /**
             * @brief Register a new Component container in the registery
             *
             * @tparam Component
             * @return Container<Component>&
             */
            template <class Component> Container<Component> &register_component(void)
            {
                try {
                    return std::any_cast<Container<Component> &>(containers.at(std::type_index(typeid(Component))));
                } catch (const std::exception &) {
                    std::any a = Container<Component>();

                    containers.emplace(std::type_index(typeid(Component)), a);
                    if (std::type_index(typeid(Component)) != std::type_index(typeid(entity_t)))
                        destructors.push_back(&destructor<Component>);
                }
                return std::any_cast<Container<Component> &>(containers.at(std::type_index(typeid(Component))));
            }

            /**
             * @brief Get the component's container specified in the template
             *
             * @tparam Component
             * @return Container<Component>&
             */
            template <class Component> Container<Component> &get_components(void)
            {
                try {
                    return std::any_cast<Container<Component> &>(containers.at(std::type_index(typeid(Component))));
                } catch (const std::out_of_range &) {
                    throw ExceptComponantNotFound<Component>();
                }
            }

            /**
             * @brief Get the component's container specified in the template
             *
             * @tparam Component
             * @return Container<Component> const&
             */
            template <class Component> Container<Component> const &get_components(void) const
            {
                try {
                    return std::any_cast<Container<Component> &>(containers.at(std::type_index(typeid(Component))));
                } catch (const std::out_of_range &) {
                    throw ExceptComponantNotFound<Component>();
                }
            }

            /**
             * @brief Spawn a new entity
             *
             * @return id of the new entity
             */
            entity_t spawn_entity();

            /**
             * @param idx
             * @return id of the idx entity
             */
            entity_t entity_from_index(std::size_t idx);

            /**
             * @brief kill an entity
             *
             * @param e
             */
            void kill_entity(entity_t const &e);

            /**
             * @brief Add a componant in the Container of its type
             *
             * @param to
             * @param c
             * @return Component &
             */
            template <typename Component> Component &add_component(entity_t const &to, Component &&c)
            {
                return register_component<Component>().insert_at(to, std::move(c));
            }

            /**
             * @brief Emplace a componant in the Container of it type
             *
             * @tparam Component
             * @tparam Params
             * @param to
             * @param p
             * @return Component&
             */
            template <typename Component, typename... Params> Component &emplace_component(entity_t const &to, Params &&...p)
            {
                return register_component<Component>().emplace_at(to, std::forward<Params>(p)...);
            }

            /**
             * @brief remove a componant
             *
             * @tparam Component
             * @param from refered entity
             */
            template <typename Component> void remove_component(entity_t const &from) { get_components<Component>().erase(from); }

            void add_system(system_t &&f) noexcept { systems.push_back(f); }
            template <class... Components, typename Function> void add_system(Function const &f) { systems.push_back(f); }
            void run_systems()
            {
                for (auto &s : systems)
                    s(*this);
                for (auto &&id : to_destroy) {
                    for (auto &d : destructors)
                        d(*this, id);
                }
                to_destroy.clear();
            }

            static bool isKeyPressed(const Keyboard::Key &key) { return Keyboard::isKeyPressed(key); }

            Window win;
            Client cli;

        private:
            template <typename Component> static void destructor(Registery &r, const entity_t &e) { r.remove_component<Component>(e); }
            using destructor_t = void (*)(Registery &, const entity_t &);

            // Initiate systems required for the Engine
            void init_basics_systems(void);
            // map of Container for each type of component
            std::unordered_map<std::type_index, std::any> containers;
            std::vector<system_t> systems;
            std::vector<destructor_t> destructors;
            std::vector<entity_t> to_destroy;
    };
} // namespace uwugine
