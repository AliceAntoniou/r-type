/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Texture
*/

#pragma once

#include "Point.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace uwugine
{
    class Texture {
        public:
            Texture(void) noexcept = default;
            Texture(const std::string &filename) noexcept;

            Texture(const Texture &) noexcept;
            Texture(Texture &&) noexcept = default;
            ~Texture(void) noexcept = default;

            Texture &operator=(const Texture &) noexcept;
            Texture &operator=(Texture &&) noexcept = default;

            void loadFromFile(const std::string &path);
            Point2i getSize(void) const noexcept;
            const sf::Texture &getHandle(void) const noexcept;

        private:
            sf::Texture texture;
    };
    /**
     * @brief Get the Texture (will load the Texture only if it has not been already load)
     *
     * @param name
     * @return Texture&
     */
    Texture &getTexture(const std::string &name);
}
