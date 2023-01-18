/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** fire
*/

#include "Fire.hpp"
#include <cmath>

static inline float get_rad(float a) { return M_PI * (a / 180); }

std::vector<uwugine::Point2u> game::Component::Fire::getSheetFrames() {
    int number_frames = 3;
    int size_frame = 34;
    std::vector<uwugine::Point2u> pos;
    uwugine::Point2u p(1, 0);

    for (size_t i = 0; i < number_frames; i++) {
        pos.push_back(p);
        p.x += size_frame;
    }
    return pos;
}

game::Component::Fire::Fire(uwugine::Registery &r, uwugine::Point2f pos, float angle, const std::string c_target) : target(c_target)
 {
    id = r.spawn_entity();
    uwugine::Sprite sprite(uwugine::getTexture("./assets/sprites/r-typesheet30a.gif"), {{0, 0}, {34, 34}});
    uwugine::Rectangle rect_hit(uwugine::Point2f{0, 0}, uwugine::Point2f{34 * 2, 34 * 2});
    uwugine::Component::hitbox hit(rect_hit, 0);
    hit.setPosition(pos);
    hit.setColideFunction(game::Systems::fireBall_collisions);
    uwugine::Component::sound sound;
    sound.loadFromFile("./assets/barrel-exploding-soundbible.wav");

    hit.setMsg("f," + std::to_string(id) + std::string(",") + target);
    sprite.setScale({2, 2});
    r.add_component(id, uwugine::Component::position{pos, pos});
    r.add_component(id, uwugine::Component::velocity{10, get_rad(angle)});
    r.add_component(id, uwugine::Component::sprite{std::move(sprite), 1, {{getSheetFrames()}}});
    r.add_component(id, uwugine::Component::animation());
    r.add_component(id, std::move(hit));
    r.add_component(id, std::move(sound));
}

void game::Component::Fire::delete_component(uwugine::Registery &r)
{
    r.kill_entity(id);
}
