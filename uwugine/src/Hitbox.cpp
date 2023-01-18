/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Hitbox
*/

#include "Hitbox.hpp"
#include "Exception.hpp"
#include <cmath>

static std::size_t new_id = 0;

uwugine::Hitbox::Hitbox(void) : id(new_id++) {}

uwugine::Hitbox::Hitbox(std::size_t layer) : hitbox_id(layer), id(new_id++) {}

uwugine::Hitbox::Hitbox(const Polygone &hitbox, std::size_t layer) : hitbox_id(layer), id(new_id++) { box = hitbox; }

void uwugine::Hitbox::setPosition(const Point2f &p) { box.setPosition(p); }

uwugine::Point2f uwugine::Hitbox::getPosition(void) { return box.getPosition(); }

uwugine::Polygone &uwugine::Hitbox::getBox(void) noexcept { return box; }

void uwugine::Hitbox::setBox(const Polygone &pol) noexcept { box = pol; }

std::size_t uwugine::Hitbox::getBoxId(void) const noexcept { return hitbox_id; }

void uwugine::Hitbox::setBoxId(std::size_t id) noexcept { hitbox_id = id; }

void uwugine::Hitbox::drawBox(Window &win) noexcept
{
    sf::VertexArray array(sf::PrimitiveType::Quads);

    for (auto &&i : box.getHandle()) {
        array.append(sf::Vertex{sf::Vector2f{i.x, i.y}, sf::Color::Red});
    }
    win.getHandle().draw(array);
}

void uwugine::Hitbox::onColide(Registery &r, const std::string &other)
{
    if (f != nullptr)
        f(r, msg, other);
}

void uwugine::Hitbox::setMsg(const std::string &str) { msg = str; }

const std::string &uwugine::Hitbox::getMsg(void) { return msg; }

bool uwugine::Hitbox::isColiding(Hitbox &h)
{
    if (id != h.id)
        return box.isIntersecting(h.box);
    return false;
}

void uwugine::Hitbox::setColideFunction(system_t &&func) { f = func; }
