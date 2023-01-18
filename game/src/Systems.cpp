/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** systems
*/

#define _USE_MATH_DEFINES
#include "Systems.hpp"
#include "Components.hpp"
#include "JSONParser.hpp"
#include "UwUgine.hpp"
#include <cmath>
#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include <string>

static inline float get_rad(float a) { return M_PI * (a / 180); }

void game::Systems::update_mobs(uwugine::Registery &r)
{
    for (uwugine::Zipper_iterator<game::Component::Player> z(r); !z.is_end(); z++) {
        auto &mob = z.get<game::Component::Player>();

        mob.move(r);
    }
    for (uwugine::Zipper_iterator<uwugine::Component::position, game::Component::Enemy> z(r); !z.is_end(); z++) {
        auto &pos = z.get<uwugine::Component::position>();
        auto &mob = z.get<game::Component::Enemy>();
        mob.move(r);
        if (pos.curent.x < -50) {
            mob.delete_component(r);
        }
    }
    for (uwugine::Zipper_iterator<uwugine::Component::position, game::Component::Fire> z(r); !z.is_end(); z++) {
        auto &pos = z.get<uwugine::Component::position>();
        auto &mob = z.get<game::Component::Fire>();
        if (pos.curent.x > 500) {
            mob.delete_component(r);
        }
        if (pos.curent.x < 0) {
            mob.delete_component(r);
        }
    }
}

void game::Systems::waves_system(uwugine::Registery &r)
{
    static int wave_index;
    if (wave_index == -1) {
        return;
    }
    JSONParser parser;
    static std::vector<EnemyWave> waves;
    static uwugine::Clock clock;
    parser.parse("./assets/enemy_waves.json");
    waves = parser.get_waves();
    int wave_size = waves.size();
    if (wave_index >= wave_size) {
        wave_index = -1;
        return;
    }
    auto clock_time = clock.getElapsedTime();
    int microsec = clock_time.asMicroseconds();
    int elapsed_time = (microsec / 100000);
    if (elapsed_time > waves[wave_index].wave_duration) {
        clock.restart();
        for (EnemyProperties &enemy : waves[wave_index].wave_enemies) {
            Component::Enemy e;
            e.create(r, enemy);
            r.add_component(e.id, std::move(e));
        }
        wave_index++;
    }
}

static std::string entity_get_type(const std::string &msg)
{
    std::string type_me = msg.substr(0, msg.find(",", 0));
    return (type_me);
}

static std::size_t entity_get_id(const std::string &msg)
{
    std::stringstream sstream(msg.substr(msg.find(",", 0) + 1, msg.find(",", msg.find(",", 0) + 1)));
    uwugine::entity_t ent;
    sstream >> ent;
    return ent;
}

static std::string entity_get_target(const std::string &msg)
{
    std::stringstream sstream(msg.substr(msg.find(",", msg.find(",", 0) + 1) + 1, std::string::npos));
    std::string ent;
    sstream >> ent;
    return ent;
}

void game::Systems::fireBall_collisions(uwugine::Registery &r, const std::string &me, const std::string &other)
{
    std::string type_me = entity_get_type(me);
    uwugine::entity_t e_me = entity_get_id(me);
    std::string target = entity_get_target(me);

    std::string type_oth = entity_get_type(other);
    uwugine::entity_t e_oth = entity_get_id(other);

    if (type_oth == target && target == "e") {
        uwugine::Component::sound &me_sound = r.get_components<uwugine::Component::sound>()[e_me];
        me_sound.play();

        game::Component::Fire &fire = r.get_components<game::Component::Fire>()[e_me];
        game::Component::Enemy &en = r.get_components<game::Component::Enemy>()[e_oth];
        en.get_damages(r, fire.power);
        fire.delete_component(r);
    } else if (type_oth == target && target == "p") {
        game::Component::Fire &fire = r.get_components<game::Component::Fire>()[e_me];
        game::Component::Player &en = r.get_components<game::Component::Player>()[e_oth];
        en.get_damages(r, fire.power);
        fire.delete_component(r);
    }
}
