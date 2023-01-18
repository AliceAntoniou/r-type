/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Point
*/

#include "Point.hpp"

uwugine::Point2f::Point2f(float x, float y) noexcept : Point(), x(x), y(y) {}

uwugine::Point2f::Point2f(const Point2i &p) noexcept
{
    x = static_cast<float>(p.x);
    y = static_cast<float>(p.y);
}

uwugine::Point2f::Point2f(const Point2u &p) noexcept
{
    x = static_cast<float>(p.x);
    y = static_cast<float>(p.y);
}

uwugine::Point2f uwugine::Point2f::operator+(const Point2f &rhs) const noexcept { return Point2f(x + rhs.x, y + rhs.y); }

void uwugine::Point2f::operator+=(const Point2f &rhs) noexcept { *this = *this + rhs; }

uwugine::Point2f uwugine::Point2f::operator-(const Point2f &rhs) const noexcept { return Point2f(x - rhs.x, y - rhs.y); }

uwugine::Point2f uwugine::Point2f::operator-() const noexcept { return Point2f(-x, -y); }

void uwugine::Point2f::operator-=(const Point2f &rhs) noexcept { *this = *this - rhs; }

uwugine::Point2f uwugine::Point2f::operator*(const Point2f &rhs) const noexcept { return Point2f(x * rhs.x, y * rhs.y); }

void uwugine::Point2f::operator*=(const Point2f &rhs) noexcept { *this = *this * rhs; }

uwugine::Point2f uwugine::Point2f::operator/(const Point2f &rhs) const noexcept { return Point2f(x / rhs.x, y / rhs.y); }

void uwugine::Point2f::operator/=(const Point2f &rhs) noexcept { *this = *this / rhs; }

bool uwugine::Point2f::operator==(const Point2f &rhs) const noexcept { return (x == rhs.x && y == rhs.y); }

bool uwugine::Point2f::operator!=(const Point2f &rhs) const noexcept { return !(*this == rhs); }

uwugine::Point2i::Point2i(int x, int y) noexcept : Point(), x(x), y(y) {}

uwugine::Point2i::Point2i(const Point2f &p) noexcept
{
    x = static_cast<int>(p.x);
    y = static_cast<int>(p.y);
}

uwugine::Point2i::Point2i(const Point2u &p) noexcept
{
    x = static_cast<int>(p.x);
    y = static_cast<int>(p.y);
}

uwugine::Point2i uwugine::Point2i::operator+(const Point2i &rhs) const noexcept { return Point2i(x + rhs.x, y + rhs.y); }

void uwugine::Point2i::operator+=(const Point2i &rhs) noexcept { *this = *this + rhs; }

uwugine::Point2i uwugine::Point2i::operator-(const Point2i &rhs) const noexcept { return Point2i(x - rhs.x, y - rhs.y); }

uwugine::Point2i uwugine::Point2i::operator-() const noexcept { return Point2i(-x, -y); }

void uwugine::Point2i::operator-=(const Point2i &rhs) noexcept { *this = *this - rhs; }

uwugine::Point2i uwugine::Point2i::operator*(const Point2i &rhs) const noexcept { return Point2i(x * rhs.x, y * rhs.y); }

void uwugine::Point2i::operator*=(const Point2i &rhs) noexcept { *this = *this * rhs; }

uwugine::Point2i uwugine::Point2i::operator/(const Point2i &rhs) const noexcept { return Point2i(x / rhs.x, y / rhs.y); }

void uwugine::Point2i::operator/=(const Point2i &rhs) noexcept { *this = *this / rhs; }

bool uwugine::Point2i::operator==(const Point2i &rhs) const noexcept { return (x == rhs.x && y == rhs.y); }

bool uwugine::Point2i::operator!=(const Point2i &rhs) const noexcept { return !(*this == rhs); }

uwugine::Point2u::Point2u(int x, int y) noexcept : Point(), x(x), y(y) {}

uwugine::Point2u::Point2u(const Point2f &p) noexcept
{
    x = static_cast<unsigned int>(p.x);
    y = static_cast<unsigned int>(p.y);
}

uwugine::Point2u::Point2u(const Point2i &p) noexcept
{
    x = static_cast<unsigned int>(p.x);
    y = static_cast<unsigned int>(p.y);
}

uwugine::Point2u uwugine::Point2u::operator+(const Point2u &rhs) const noexcept { return Point2u(x + rhs.x, y + rhs.y); }

void uwugine::Point2u::operator+=(const Point2u &rhs) noexcept { *this = *this + rhs; }

uwugine::Point2u uwugine::Point2u::operator-(const Point2u &rhs) const noexcept { return Point2u(x - rhs.x, y - rhs.y); }

uwugine::Point2u uwugine::Point2u::operator-() const noexcept { return Point2u(-x, -y); }

void uwugine::Point2u::operator-=(const Point2u &rhs) noexcept { *this = *this - rhs; }

uwugine::Point2u uwugine::Point2u::operator*(const Point2u &rhs) const noexcept { return Point2u(x * rhs.x, y * rhs.y); }

void uwugine::Point2u::operator*=(const Point2u &rhs) noexcept { *this = *this * rhs; }

uwugine::Point2u uwugine::Point2u::operator/(const Point2u &rhs) const noexcept { return Point2u(x / rhs.x, y / rhs.y); }

void uwugine::Point2u::operator/=(const Point2u &rhs) noexcept { *this = *this / rhs; }

bool uwugine::Point2u::operator==(const Point2u &rhs) const noexcept { return (x == rhs.x && y == rhs.y); }

bool uwugine::Point2u::operator!=(const Point2u &rhs) const noexcept { return !(*this == rhs); }
