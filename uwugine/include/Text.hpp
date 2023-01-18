/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Text
*/

#pragma once

#include "Polygone.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace uwugine
{
    class Font {
        public:
            Font(void) noexcept = default;
            Font(const std::string &filename) noexcept;

            Font(const Font &) noexcept = default;
            Font(Font &&) noexcept = default;
            ~Font(void) noexcept = default;

            Font &operator=(const Font &) noexcept = default;
            Font &operator=(Font &&) noexcept = default;

            void loadFromFile(const std::string &filename) noexcept;
            const sf::Font &getHandle(void) const noexcept;

        private:
            sf::Font font;
    };
    /**
     * @brief Get the Font (will load the Font only if it has not been already load)
     *
     * @param filename
     * @return Font&
     */
    Font &getFont(const std::string &filename);
    class Text {
        public:
            Text(void) = default;
            Text(const Font &texture, const std::string &) noexcept;
            Text(const Font &texture, const std::string &, const sf::Color &) noexcept;

            Text(const Text &) = default;
            Text(Text &&) noexcept = default;
            ~Text(void) noexcept = default;

            Text &operator=(const Text &) = default;
            Text &operator=(Text &&) noexcept = default;

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
             * @brief Set the Font
             *
             */
            void setFont(const Font &) noexcept;

            /**
             * @brief Set the String
             *
             */
            void setString(const std::string &);
            /**
             * @brief Get the String
             *
             * @return std::string
             */
            std::string getString(void);

            /**
             * @brief Set the Scale
             *
             */
            void setScale(const Point2f &) noexcept;
            /**
             * @brief Get the Scale
             *
             * @return Point2f
             */
            Point2f getScale(void) const noexcept;
            /**
             * @brief Get the Global Bounds
             *
             * @return Rectangle
             */
            Rectangle getGlobalBounds(void) const;

            /**
             * @brief Set the Fill Color
             *
             */
            void setFillColor(const sf::Color &) noexcept;
            /**
             * @brief Get the Fill Color
             *
             * @return const sf::Color&
             */
            const sf::Color &getFillColor() const noexcept;
            /**
             * @brief Set the Outline Color
             *
             */
            void setOutlineColor(const sf::Color &) noexcept;
            /**
             * @brief Get the Outline Color
             *
             * @return const sf::Color&
             */
            const sf::Color &getOutlineColor() const noexcept;

            std::unique_ptr<sf::Drawable> getDrawable(void) const;

        private:
            sf::Text text;
    };
} // namespace uwugine
