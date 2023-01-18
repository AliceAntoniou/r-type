/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Drawable
*/

#include "Sprite.hpp"
#include "Window.hpp"

sf::IntRect getIntRect(const uwugine::Rectangle &rect)
{
    return sf::IntRect{(int) rect.getPosition().x, (int) rect.getPosition().y, (int) rect.getSize().x, (int) rect.getSize().y};
}

uwugine::Sprite::Sprite(const Texture &texture) noexcept { sprite.setTexture(texture.getHandle()); }

uwugine::Sprite::Sprite(const Texture &texture, const Rectangle &rect) noexcept
{
    sprite.setTexture(texture.getHandle());
    setTextureRect(rect);
}

void uwugine::Sprite::setPosition(const Point2f &p) noexcept { sprite.setPosition(sf::Vector2f{p.x, p.y}); }

uwugine::Point2f uwugine::Sprite::getPosition(void) const noexcept
{
    sf::Vector2f p = sprite.getPosition();

    return Point2f{p.x, p.y};
}

void uwugine::Sprite::setTexture(const Texture &texture) { sprite.setTexture(texture.getHandle()); }

void uwugine::Sprite::setTextureRect(const Rectangle &r)
{
    sf::IntRect rect = {static_cast<int>(r.getPosition().x), static_cast<int>(r.getPosition().y), static_cast<int>(r.getSize().x),
        static_cast<int>(r.getSize().y)};

    sprite.setTextureRect(rect);
}

uwugine::Rectangle uwugine::Sprite::getTextureRect(void) const noexcept
{
    sf::IntRect rect = sprite.getTextureRect();

    return Rectangle{
        {static_cast<float>(rect.left), static_cast<float>(rect.top)}, {static_cast<float>(rect.width), static_cast<float>(rect.height)}};
}

void uwugine::Sprite::setScale(const Point2f &p) { sprite.setScale(sf::Vector2f{p.x, p.y}); }

uwugine::Point2f uwugine::Sprite::getScale(void) const
{
    sf::Vector2f p = sprite.getScale();

    return Point2f{p.x, p.y};
}

uwugine::Rectangle uwugine::Sprite::getGlobalBounds(void) const
{
    sf::FloatRect rect = sprite.getGlobalBounds();

    return Rectangle{Point2f{rect.left, rect.top}, Point2f{rect.width, rect.height}};
}

std::unique_ptr<sf::Drawable> uwugine::Sprite::getDrawable(void) const { return std::make_unique<sf::Sprite>(sprite); }