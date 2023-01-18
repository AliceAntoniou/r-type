/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** object
*/

#pragma once

#include "Polygone.hpp"
#include "Registery.hpp"
#include "Window.hpp"

namespace uwugine
{
    class Hitbox {
            using system_t = void (*)(uwugine::Registery &, const std::string &, const std::string &);

        public:
            Hitbox(void);
            Hitbox(std::size_t id);
            Hitbox(const Polygone &hitbox, std::size_t id = 0);

            Hitbox(const Hitbox &) = default;
            Hitbox(Hitbox &&) noexcept = default;
            ~Hitbox(void) noexcept = default;

            Hitbox &operator=(const Hitbox &rhs) = default;
            Hitbox &operator=(Hitbox &&rhs) noexcept = default;

            /**
             * @brief Get the Box object
             *
             * @return Polygone&
             */
            Polygone &getBox(void) noexcept;
            /**
             * @brief Set the Box object
             *
             */
            void setBox(const Polygone &) noexcept;

            /**
             * @brief Get the Box Id object
             *
             * @return std::size_t
             */
            std::size_t getBoxId(void) const noexcept;
            /**
             * @brief Set the Box Id object
             *
             */
            void setBoxId(std::size_t) noexcept;

            /**
             * @brief Set the Position
             *
             */
            void setPosition(const Point2f &);
            /**
             * @brief Get the Position
             *
             * @return Point2f
             */
            Point2f getPosition(void);

            /**
             * @return true The two hitboxes are colinding
             * @return false The two hitboxes are not colinding
             */
            bool isColiding(Hitbox &);
            /**
             * @brief Set the Colide Function
             * @brief The fonction will be called if two hitbox colide
             *
             */
            void setColideFunction(system_t &&);

            void drawBox(Window &) noexcept;

            void onColide(Registery &, const std::string &msg);
            /**
             * @brief Set the Msg send to other hiboxes
             *
             */
            void setMsg(const std::string &);
            /**
             * @brief Get the Msg object
             *
             * @return const std::string&
             */
            const std::string &getMsg(void);

        protected:
            Polygone box;
            std::size_t hitbox_id = 0;
            system_t f = nullptr;

        private:
            std::string msg;
            std::size_t id;
    };
}
