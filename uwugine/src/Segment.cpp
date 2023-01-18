/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Segment
*/

#include "Segment.hpp"

uwugine::Segment2f::Segment2f(const Point2f &a, const Point2f &b) noexcept : Segment(), a(a), b(b) {}

bool uwugine::Segment2f::isIntersecting(const Segment2f &seg)
{
    Point2f s1;
    Point2f s2;
    float s;
    float t;

    s1.x = b.x - a.x;
    s1.y = b.y - a.y;
    s2.x = seg.b.x - seg.a.x;
    s2.y = seg.b.y - seg.a.y;

    s = (-s1.y * (a.x - seg.a.x) + s1.x * (a.y - seg.a.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = (s2.x * (a.y - seg.a.y) - s2.y * (a.x - seg.a.x)) / (-s2.x * s1.y + s1.x * s2.y);

    return (s >= 0 && s <= 1 && t >= 0 && t <= 1);
}
