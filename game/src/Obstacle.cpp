/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Obstacle
*/

#define _USE_MATH_DEFINES
#include <cmath>
#include "Obstacle.hpp"
#include "Components.hpp"
#include <sstream>

static std::vector<uwugine::Point2u> getSheetFrames(size_t number_frames, int size_frame)
{
    std::vector<uwugine::Point2u> pos;
    uwugine::Point2u p(1, 0);

    for (size_t i = 0; i < number_frames; i++) {
        pos.push_back(p);
        p.x += size_frame;
    }
    return pos;
}

static inline float get_rad(float a) { return M_PI * (a / 180); }

static std::string entity_get_type(const std::string &msg)
{
    std::string type_me = msg.substr(0, msg.find(",", 0));
    return (type_me);
}

static std::size_t entity_get_id(const std::string &msg)
{
    std::stringstream sstream(msg.substr(msg.find(",", 0) + 1, std::string::npos));
    uwugine::entity_t ent;
    sstream >> ent;
    return ent;
}

void obstacle_collisions(uwugine::Registery &r, const std::string &me, const std::string &other)
{
    std::string type_oth = entity_get_type(other);
    uwugine::entity_t e_oth = entity_get_id(other);

    if (type_oth == "p") {
        game::Component::Player &p = r.get_components<game::Component::Player>()[e_oth];
        p.is_colliding = true;
    }
}

void game::Component::Obstacle::create(uwugine::Registery &r, struct ObstaclesProperties proprieties)
{
    float x = proprieties.x;
    float y = proprieties.y;
    float size_frame_x = proprieties.sprite_size.first;
    float size_frame_y = proprieties.sprite_size.second;
    int nb_frames = proprieties.sprite_nb_frames;
    float scale =proprieties.scale;
    std::string file_name = proprieties.sprite_path;

    id = r.spawn_entity();
    uwugine::Sprite sprite(uwugine::getTexture(file_name), {{0, 0}, {size_frame_x, size_frame_y}});
    uwugine::Component::hitbox hit = {uwugine::Rectangle(uwugine::Point2f{x, y}, uwugine::Point2f{size_frame_x * scale, size_frame_y * scale}), 0};

    sprite.setScale({scale, scale});
    hit.setMsg("o," + std::to_string(id));
    hit.setColideFunction(obstacle_collisions);

    r.add_component(id, uwugine::Component::position{uwugine::Point2f{x, y}, uwugine::Point2f{x, y}});
    r.add_component(id, uwugine::Component::velocity{1, get_rad(180)});
    r.add_component(id, uwugine::Component::sprite{std::move(sprite), 1, {{getSheetFrames(nb_frames, size_frame_x)}}});
    r.add_component(id, uwugine::Component::animation());
    r.add_component(id, std::move(hit));
}

void game::Component::Obstacle::delete_component(uwugine::Registery &r)
{
    r.kill_entity(id);
}
