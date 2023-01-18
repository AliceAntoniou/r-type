/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Clock
*/

#include <SFML/System.hpp>

#pragma once

namespace uwugine
{
    namespace Time_unit
    {
        constexpr int64_t SECONDE = 1000000;
        constexpr int64_t MILISECONDE = 1000;
        constexpr int64_t MICROSECONDE = 1;
    }
    class Time {
        public:
            Time(void) noexcept = default;
            Time(int64_t microseconds) noexcept;

            Time(const Time &) noexcept = delete;
            Time(Time &&) noexcept = default;
            ~Time(void) noexcept = default;

            Time &operator=(const Time &) noexcept = delete;
            Time &operator=(Time &&) noexcept = default;

            Time operator-(const Time &) const noexcept;
            Time operator+(const Time &) const noexcept;

            bool operator==(const Time &) const noexcept;
            bool operator<(const Time &) const noexcept;
            bool operator<=(const Time &) const noexcept;
            bool operator>(const Time &) const noexcept;
            bool operator>=(const Time &) const noexcept;

            /**
             * @brief Return the time as microseconds
             *
             * @return int64_t
             */
            int64_t asMicroseconds() const noexcept;
            /**
             * @brief Return the time as milliseconds
             *
             * @return int32_t
             */
            int32_t asMilliseconds() const noexcept;
            /**
             * @brief Return the time as seconds
             *
             * @return float
             */
            float asSeconds() const noexcept;

        private:
            int64_t microseconds;
    };
    class Clock {
        public:
            Clock(void);

            Clock(const Clock &) noexcept = default;
            Clock(Clock &&) noexcept = default;
            ~Clock(void) noexcept = default;

            Clock &operator=(const Clock &) noexcept = default;
            Clock &operator=(Clock &&) noexcept = default;

            /**
             * @brief Get the elapsed time between now and the last restart
             *
             * @return uwugine::Time
             */
            uwugine::Time getElapsedTime() const;
            /**
             * @brief Restart the clock
             *
             * @return uwugine::Time
             */
            uwugine::Time restart();

        private:
            clock_t time;
    };
    class Timer {
        public:
            Timer(void) noexcept = default;
            Timer(Time) noexcept;

            Timer(const Timer &) noexcept = default;
            Timer(Timer &&) noexcept = default;
            ~Timer(void) noexcept = default;

            Timer &operator=(const Timer &) noexcept = default;
            Timer &operator=(Timer &&) noexcept = default;

            /**
             * @brief Give how many time left befor timer end
             *
             * @return Time
             */
            Time left(void) const noexcept;
            /**
             * @return true The timer has ended
             * @return false The timer has not ended
             */
            bool done() const noexcept;
            /**
             * @brief Set the timer to a new time
             *
             */
            void set(Time) noexcept;

        private:
            Time time;
            Clock clock;
    };
} // namespace uwugine
