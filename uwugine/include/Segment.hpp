/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Segment
*/

#pragma once

#include "Point.hpp"

namespace uwugine
{
    class Segment {
        public:
            Segment(void) noexcept = default;

            Segment(const Segment &) noexcept = default;
            Segment(Segment &&) noexcept = default;
            virtual ~Segment(void) noexcept = default;

            Segment &operator=(const Segment &) noexcept = default;
            Segment &operator=(Segment &&) noexcept = default;
    };
    class Segment2f : public Segment {
        public:
            Segment2f(void) noexcept = default;
            Segment2f(const Point2f &a, const Point2f &b) noexcept;

            Segment2f(const Segment2f &) noexcept = default;
            Segment2f(Segment2f &&) noexcept = default;
            ~Segment2f(void) noexcept final = default;

            Segment2f &operator=(const Segment2f &) noexcept = default;
            Segment2f &operator=(Segment2f &&) noexcept = default;

            bool isIntersecting(const Segment2f &);

            Point2f a;
            Point2f b;
    };
}
