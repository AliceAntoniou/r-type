/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Text
*/

#include "Text.hpp"

uwugine::Text::Text(const Font &font, const std::string &msg) noexcept : text(msg, font.getHandle()) {}

uwugine::Text::Text(const Font &font, const std::string &msg, const sf::Color &c) noexcept : text(msg, font.getHandle())
{
    setFillColor(c);
    setOutlineColor(c);
    text.setCharacterSize(20);
}

void uwugine::Text::setPosition(const Point2f &p) noexcept { text.setPosition(sf::Vector2f{p.x, p.y}); }

uwugine::Point2f uwugine::Text::getPosition(void) const noexcept
{
    sf::Vector2f p = text.getPosition();

    return Point2f{p.x, p.y};
}

void uwugine::Text::setFont(const Font &font) noexcept { text.setFont(font.getHandle()); }

void uwugine::Text::setString(const std::string &msg) { text.setString(msg); }

std::string uwugine::Text::getString(void) { return text.getString(); }

void uwugine::Text::setScale(const Point2f &p) noexcept { text.setScale(sf::Vector2f{p.x, p.y}); }

uwugine::Point2f uwugine::Text::getScale(void) const noexcept
{
    sf::Vector2f p = text.getScale();

    return Point2f{p.x, p.y};
}

uwugine::Rectangle uwugine::Text::getGlobalBounds(void) const
{
    sf::FloatRect rect = text.getGlobalBounds();

    return Rectangle{Point2f{rect.left, rect.top}, Point2f{rect.width, rect.height}};
}

void uwugine::Text::setFillColor(const sf::Color &c) noexcept { text.setFillColor(c); }

const sf::Color &uwugine::Text::getFillColor() const noexcept { return text.getFillColor(); }

void uwugine::Text::setOutlineColor(const sf::Color &c) noexcept { text.setOutlineColor(c); }

const sf::Color &uwugine::Text::getOutlineColor() const noexcept { return text.getOutlineColor(); }

std::unique_ptr<sf::Drawable> uwugine::Text::getDrawable(void) const { return std::make_unique<sf::Text>(text); }

uwugine::Font::Font(const std::string &filename) noexcept { loadFromFile(filename); }

void uwugine::Font::loadFromFile(const std::string &path) noexcept { font.loadFromFile(path); }

const sf::Font &uwugine::Font::getHandle(void) const noexcept { return font; }

uwugine::Font &uwugine::getFont(const std::string &filename)
{
    static std::map<std::string, uwugine::Font> fonts;

    try {
        return fonts.at(filename);
    } catch (const std::out_of_range &) {
        fonts.emplace(filename, filename);
    }
    return fonts.at(filename);
}
