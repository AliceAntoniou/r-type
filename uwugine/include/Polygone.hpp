/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Polygone
*/

#pragma once

#include "Segment.hpp"
#include <vector>

namespace uwugine
{
    class Polygone {
        public:
            Polygone(void) = default;

            Polygone(const Polygone &) = default;
            Polygone(Polygone &&) noexcept = default;
            ~Polygone(void) noexcept = default;

            Polygone &operator=(const Polygone &) = default;
            Polygone &operator=(Polygone &&) noexcept = default;

            void pushBackPoint(const Point2f &);

            void setPosition(const Point2f &);
            Point2f getPosition(void) const;
            void move(const Point2f &);

            bool isIntersecting(const Polygone &) const;
            bool isIntersecting(const Segment2f &) const;
            bool isContaining(const Polygone &) const;
            bool isContaining(const Segment2f &) const;
            bool isContaining(const Point2f &) const;

            std::vector<Point2f> &getHandle(void);

        protected:
            std::vector<Point2f> points;
    };
    class Rectangle : public Polygone {
        public:
            Rectangle(void) = default;
            Rectangle(const Point2f &size) noexcept;
            Rectangle(const Point2f &pos, const Point2f &size) noexcept;

            Rectangle(const Rectangle &) = default;
            Rectangle(Rectangle &&) noexcept = default;
            ~Rectangle(void) noexcept = default;

            Rectangle &operator=(const Rectangle &) = default;
            Rectangle &operator=(Rectangle &&) noexcept = default;

            void setPosition(const Point2f &);
            Point2f getPosition(void) const;
            void setSize(const Point2f &);
            Point2f getSize(void) const;

            Point2f &top_left(void);
            Point2f &top_right(void);
            Point2f &bot_left(void);
            Point2f &bot_right(void);
    };
}
