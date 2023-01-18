/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Texture
*/

#include "Texture.hpp"
#include <map>

uwugine::Texture::Texture(const std::string &filename) noexcept { texture.loadFromFile(filename); }

void uwugine::Texture::loadFromFile(const std::string &filename) { texture.loadFromFile(filename); }

uwugine::Point2i uwugine::Texture::getSize(void) const noexcept
{
    sf::Vector2u s = texture.getSize();

    return Point2i{static_cast<int>(s.x), static_cast<int>(s.y)};
}

const sf::Texture &uwugine::Texture::getHandle(void) const noexcept { return texture; }

uwugine::Texture &uwugine::getTexture(const std::string &filename)
{
    static std::map<std::string, uwugine::Texture> textures;

    try {
        return textures.at(filename);
    } catch (const std::out_of_range &) {
        textures.emplace(filename, filename);
    }
    return textures.at(filename);
}