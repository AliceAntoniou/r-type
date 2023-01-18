/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Sound
*/

#include "Sound.hpp"
#include <map>

uwugine::Sound::Sound(const sf::SoundBuffer &buff) noexcept : sound(buff) {}

uwugine::Sound::Sound(const std::string &filename) noexcept : sound(getSoundBuffer(filename)) {}

void uwugine::Sound::setBuffer(const sf::SoundBuffer &buff) { sound.setBuffer(buff); }

void uwugine::Sound::loadFromFile(const std::string &filename) { sound.setBuffer(getSoundBuffer(filename)); }

const sf::Sound &uwugine::Sound::getHandle(void) const noexcept { return sound; }

void uwugine::Sound::play(void) { sound.play(); }

void uwugine::Sound::pause(void) { sound.pause(); }

void uwugine::Sound::setLoop(bool loop) { sound.setLoop(loop); }

bool uwugine::Sound::getLoop(void) { return sound.getLoop(); }

void uwugine::Sound::setVolume(float v) { sound.setVolume(v); }

float uwugine::Sound::getVolume(void) { return sound.getVolume(); }

void uwugine::Sound::setPitch(float p) { sound.setPitch(p); }

float uwugine::Sound::getPitch(void) { return sound.getPitch(); }

sf::SoundBuffer &uwugine::getSoundBuffer(const std::string &filename)
{
    static std::map<std::string, sf::SoundBuffer> sounds;
    sf::SoundBuffer buff;

    try {
        return sounds.at(filename);
    } catch (const std::out_of_range &) {
        buff.loadFromFile(filename);
        sounds.emplace(filename, buff);
    }
    return sounds.at(filename);
}