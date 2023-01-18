/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** background
*/

#include "Background.hpp"

static inline float get_rad(float a) { return M_PI * (a / 180); }

std::vector<uwugine::Point2u> game::Component::Background::getSheetFrames() {
    int number_frames = 700;
    int size_frame = 1;
    std::vector<uwugine::Point2u> pos;
    uwugine::Point2u p(1, 0);

    for (size_t i = 0; i < number_frames; i++) {
        pos.push_back(p);
        p.x += size_frame;
    }
    return pos;
}

game::Component::Background::Background(uwugine::Registery &r)
{
    id = r.spawn_entity();
    uwugine::Sprite sprite(uwugine::getTexture("./assets/sprites/background.png"), {{0, 0}, {300, 300}});

    sprite.setScale({2, 2});
    r.add_component(id, uwugine::Component::position{{1, 0}, {0, 0}});
    r.add_component(id, uwugine::Component::velocity{1, get_rad(180)});
    r.add_component(id, uwugine::Component::sprite{std::move(sprite), 0, {{getSheetFrames()}}});
    r.add_component(id, uwugine::Component::animation());
}

void game::Component::Background::delete_component(uwugine::Registery &r)
{
    r.kill_entity(id);
}