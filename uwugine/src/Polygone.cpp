/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Polygone
*/

#include "Polygone.hpp"

void uwugine::Polygone::pushBackPoint(const Point2f &p) { points.push_back(p); }

bool uwugine::Polygone::isIntersecting(const Polygone &polygone) const
{
    Segment2f seg;

    for (std::size_t i = 0; i < polygone.points.size() - 1; i++) {
        seg.a = polygone.points[i];
        seg.b = polygone.points[i + 1];
        if (isIntersecting(seg))
            return true;
    }
    seg.a = polygone.points[0];
    seg.b = polygone.points[polygone.points.size() - 1];
    if (isIntersecting(seg))
        return true;
    return false;
}

bool uwugine::Polygone::isIntersecting(const Segment2f &seg_b) const
{
    Segment2f seg_a;

    for (std::size_t i = 0; i < points.size() - 1; i++) {
        seg_a.a = points[i];
        seg_a.b = points[i + 1];
        if (seg_a.isIntersecting(seg_b))
            return true;
    }
    seg_a.a = points[0];
    seg_a.b = points[points.size() - 1];
    if (seg_a.isIntersecting(seg_b))
        return true;
    return false;
}

bool uwugine::Polygone::isContaining(const Polygone &) const { return false; }

bool uwugine::Polygone::isContaining(const Segment2f &) const { return false; }

bool uwugine::Polygone::isContaining(const Point2f &) const { return false; }

void uwugine::Polygone::setPosition(const Point2f &pos)
{
    Point2f base = points[0];

    for (auto &p : points) {
        p -= base;
        p += pos;
    }
}

uwugine::Point2f uwugine::Polygone::getPosition(void) const { return points[0]; }

void uwugine::Polygone::move(const Point2f &pos)
{
    for (auto &p : points) {
        p += pos;
    }
}

std::vector<uwugine::Point2f> &uwugine::Polygone::getHandle(void) { return points; }

uwugine::Rectangle::Rectangle(const Point2f &size) noexcept : Polygone()
{
    const Point2f pos(0, 0);

    points.push_back(pos);
    points.emplace_back(pos.x + size.x, pos.y);
    points.emplace_back(pos.x + size.x, pos.y + size.y);
    points.emplace_back(pos.x, pos.y + size.y);
}

uwugine::Rectangle::Rectangle(const Point2f &pos, const Point2f &size) noexcept : Polygone()
{
    points.push_back(pos);
    points.emplace_back(pos.x + size.x, pos.y);
    points.emplace_back(pos.x + size.x, pos.y + size.y);
    points.emplace_back(pos.x, pos.y + size.y);
}

void uwugine::Rectangle::setPosition(const Point2f &p)
{
    top_right() = top_right() - getPosition() + p;
    bot_left() = bot_left() - getPosition() + p;
    bot_right() = bot_right() - getPosition() + p;
    top_left() = p;
}

uwugine::Point2f uwugine::Rectangle::getPosition(void) const { return points[0]; }

void uwugine::Rectangle::setSize(const Point2f &p)
{
    top_right().x = getPosition().x + p.x;
    bot_right() = getPosition() + p;
    bot_left().y = getPosition().y + p.y;
    top_left() = p;
}

uwugine::Point2f uwugine::Rectangle::getSize(void) const { return points[2] - getPosition(); }

uwugine::Point2f &uwugine::Rectangle::top_left(void) { return points[0]; }

uwugine::Point2f &uwugine::Rectangle::top_right(void) { return points[1]; }

uwugine::Point2f &uwugine::Rectangle::bot_left(void) { return points[3]; }

uwugine::Point2f &uwugine::Rectangle::bot_right(void) { return points[2]; }
