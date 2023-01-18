/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Utils
*/

#pragma once

namespace uwugine
{
    class Point {
        public:
            Point(void) noexcept = default;

            Point(const Point &) noexcept = default;
            Point(Point &&) noexcept = default;
            virtual ~Point(void) noexcept = default;

            Point &operator=(const Point &rhs) noexcept = default;
            Point &operator=(Point &&rhs) noexcept = default;
    };

    class Point2i;
    class Point2u;
    class Point2f : public Point {
        public:
            Point2f(void) noexcept = default;
            Point2f(float x, float y) noexcept;

            Point2f(const Point2f &) noexcept = default;
            Point2f(Point2f &&) noexcept = default;
            ~Point2f(void) noexcept final = default;

            Point2f &operator=(const Point2f &rhs) noexcept = default;
            Point2f &operator=(Point2f &&rhs) noexcept = default;

            Point2f(const Point2i &) noexcept;
            Point2f(const Point2u &) noexcept;

            Point2f operator+(const Point2f &rhs) const noexcept;
            void operator+=(const Point2f &rhs) noexcept;
            Point2f operator-(const Point2f &rhs) const noexcept;
            Point2f operator-(void) const noexcept;
            void operator-=(const Point2f &rhs) noexcept;
            Point2f operator*(const Point2f &rhs) const noexcept;
            void operator*=(const Point2f &rhs) noexcept;
            Point2f operator/(const Point2f &rhs) const noexcept;
            void operator/=(const Point2f &rhs) noexcept;

            bool operator==(const Point2f &rhs) const noexcept;
            bool operator!=(const Point2f &rhs) const noexcept;

            float x = 0;
            float y = 0;
    };

    class Point2i : public Point {
        public:
            Point2i(void) noexcept = default;
            Point2i(int x, int y) noexcept;

            Point2i(const Point2i &) noexcept = default;
            Point2i(Point2i &&) noexcept = default;
            ~Point2i(void) noexcept final = default;

            Point2i &operator=(const Point2i &rhs) noexcept = default;
            Point2i &operator=(Point2i &&rhs) noexcept = default;

            Point2i(const Point2f &) noexcept;
            Point2i(const Point2u &) noexcept;

            Point2i operator+(const Point2i &rhs) const noexcept;
            void operator+=(const Point2i &rhs) noexcept;
            Point2i operator-(const Point2i &rhs) const noexcept;
            Point2i operator-(void) const noexcept;
            void operator-=(const Point2i &rhs) noexcept;
            Point2i operator*(const Point2i &rhs) const noexcept;
            void operator*=(const Point2i &rhs) noexcept;
            Point2i operator/(const Point2i &rhs) const noexcept;
            void operator/=(const Point2i &rhs) noexcept;

            bool operator==(const Point2i &rhs) const noexcept;
            bool operator!=(const Point2i &rhs) const noexcept;

            int x = 0;
            int y = 0;
    };

    class Point2u : public Point {
        public:
            Point2u(void) noexcept = default;
            Point2u(int x, int y) noexcept;

            Point2u(const Point2u &) noexcept = default;
            Point2u(Point2u &&) noexcept = default;
            ~Point2u(void) noexcept final = default;

            Point2u &operator=(const Point2u &rhs) noexcept = default;
            Point2u &operator=(Point2u &&rhs) noexcept = default;

            Point2u(const Point2i &) noexcept;
            Point2u(const Point2f &) noexcept;

            Point2u operator+(const Point2u &rhs) const noexcept;
            void operator+=(const Point2u &rhs) noexcept;
            Point2u operator-(const Point2u &rhs) const noexcept;
            Point2u operator-(void) const noexcept;
            void operator-=(const Point2u &rhs) noexcept;
            Point2u operator*(const Point2u &rhs) const noexcept;
            void operator*=(const Point2u &rhs) noexcept;
            Point2u operator/(const Point2u &rhs) const noexcept;
            void operator/=(const Point2u &rhs) noexcept;

            bool operator==(const Point2u &rhs) const noexcept;
            bool operator!=(const Point2u &rhs) const noexcept;

            unsigned int x = 0;
            unsigned int y = 0;
    };
}
