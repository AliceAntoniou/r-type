/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Sound
*/

#pragma once

#include "Point.hpp"
#include <SFML/Audio.hpp>
#include <string>

namespace uwugine
{
    sf::SoundBuffer &getSoundBuffer(const std::string &name);
    class Sound {
        public:
            Sound(void) = default;
            Sound(const sf::SoundBuffer &buff) noexcept;
            Sound(const std::string &filename) noexcept;

            Sound(const Sound &) = default;
            Sound(Sound &&) noexcept = default;
            ~Sound(void) noexcept = default;

            Sound &operator=(const Sound &) = default;
            Sound &operator=(Sound &&) noexcept = default;

            void setBuffer(const sf::SoundBuffer &buff);
            void loadFromFile(const std::string &filename);
            const sf::Sound &getHandle(void) const noexcept;

            void play(void);
            void pause(void);

            void setLoop(bool);
            bool getLoop(void);

            void setVolume(float);
            float getVolume(void);

            void setPitch(float);
            float getPitch(void);

        private:
            sf::Sound sound;
    };
} // namespace uwugine
