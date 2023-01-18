/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Clock
*/

#include "Clock.hpp"
#include <ctime>

uwugine::Time::Time(int64_t _microseconds) noexcept : microseconds(_microseconds){};

uwugine::Time uwugine::Time::operator-(const Time &t) const noexcept { return microseconds - t.microseconds; }

uwugine::Time uwugine::Time::operator+(const Time &t) const noexcept { return microseconds + t.microseconds; }

bool uwugine::Time::operator==(const Time &t) const noexcept { return microseconds == t.microseconds; }

bool uwugine::Time::operator<(const Time &t) const noexcept { return microseconds < t.microseconds; }

bool uwugine::Time::operator<=(const Time &t) const noexcept { return microseconds <= t.microseconds; }

bool uwugine::Time::operator>(const Time &t) const noexcept { return microseconds > t.microseconds; }

bool uwugine::Time::operator>=(const Time &t) const noexcept { return microseconds >= t.microseconds; }

int64_t uwugine::Time::asMicroseconds() const noexcept { return microseconds; }

int32_t uwugine::Time::asMilliseconds() const noexcept { return microseconds / 1000; }

float uwugine::Time::asSeconds() const noexcept
{
    float milisecond = asMilliseconds();

    return milisecond / 1000;
}

uwugine::Clock::Clock(void) : time(clock()) {}

uwugine::Time uwugine::Clock::getElapsedTime() const { return Time(clock() - time).asMicroseconds() * 5; }

uwugine::Time uwugine::Clock::restart()
{
    Time t = getElapsedTime();
    time = clock();
    return t;
}

uwugine::Timer::Timer(Time _time) noexcept : time(std::move(_time)) {}

uwugine::Time uwugine::Timer::left(void) const noexcept
{
    if (time - clock.getElapsedTime() > 0)
        return (time - clock.getElapsedTime());
    return 0;
}

bool uwugine::Timer::done() const noexcept { return time - clock.getElapsedTime() <= 0; }

void uwugine::Timer::set(Time t) noexcept
{
    time = std::move(t);
    clock.restart();
}
