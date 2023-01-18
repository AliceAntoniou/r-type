/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Sprite
*/

#pragma once

#include "Polygone.hpp"
#include "Texture.hpp"

namespace uwugine
{
    class Sprite {
        public:
            Sprite(void) = default;
            Sprite(const Texture &texture) noexcept;
            Sprite(const Texture &texture, const Rectangle &rect) noexcept;

            Sprite(const Sprite &) = default;
            Sprite(Sprite &&) noexcept = default;
            ~Sprite(void) noexcept = default;

            Sprite &operator=(const Sprite &rhs) = default;
            Sprite &operator=(Sprite &&rhs) noexcept = default;

            /**
             * @brief Set the Position
             *
             */
            void setPosition(const Point2f &) noexcept;
            /**
             * @brief Get the Position
             *
             * @return Point2f
             */
            Point2f getPosition(void) const noexcept;

            /**
             * @brief Set the Texture
             *
             */
            void setTexture(const Texture &);

            /**
             * @brief Set the Texture Rect
             *
             */
            void setTextureRect(const Rectangle &);
            /**
             * @brief Get the Texture Rect
             *
             * @return Rectangle
             */
            Rectangle getTextureRect(void) const noexcept;
            /**
             * @brief Set the Scale
             *
             */
            void setScale(const Point2f &);
            /**
             * @brief Get the Scale
             *
             * @return Point2f
             */
            Point2f getScale(void) const;
            /**
             * @brief Get the Global Bounds
             *
             * @return Rectangle
             */
            Rectangle getGlobalBounds(void) const;

            std::unique_ptr<sf::Drawable> getDrawable(void) const;

        private:
            sf::Sprite sprite;
    };
}