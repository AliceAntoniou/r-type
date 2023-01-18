/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Basic_Components
*/

#pragma once

#include "Bindings.hpp"
#include "Clock.hpp"
#include "Hitbox.hpp"
#include "Multi_Components.hpp"
#include "Polygone.hpp"
#include "Sound.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stack>

namespace uwugine::Component
{
    using controllable = std::stack<Event>;
    typedef float gravity;
    struct sprite {
            Sprite sprite;
            size_t layer;
            struct {
                    std::vector<std::vector<Point2u>> frames_pos;
                    int64_t frame_duration = Time_unit::SECONDE;
                    std::size_t curent_frame = 0;
                    Clock clock;
            } animation;
            bool to_draw = true;
    };
    struct animation {
            size_t idx = 0;
            bool refresh = true;
    };
    struct text {
            Text txt;
            size_t layer;
            bool to_draw = true;
    };
    using sound = Sound;
    using sprite_vector = std::vector<sprite>;
    using text_vector = std::vector<text>;
    using sound_vector = std::vector<sound>;
    using hitbox = Hitbox;
} // namespace uwugine::Component
