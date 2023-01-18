/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Components
*/

#define _USE_MATH_DEFINES
#include "Components.hpp"
#include "Errors.hpp"
#include "Systems.hpp"
#include <cmath>
#include <fstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string slash = "\\";
#else
static const std::string slash = "/";
#endif

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

void game::Component::AMob::get_damages(uwugine::Registery &r, int damages)
{
    PV -= damages;
    if (PV <= 0) {
        delete_component(r);
    }
}

void game::Component::AMob::delete_component(uwugine::Registery &r) { r.kill_entity(id); }

void game::Component::Enemy::move(uwugine::Registery &r)
{
    auto &clock = r.get_components<uwugine::Clock>()[id];

    if (clock.getElapsedTime() >= uwugine::Time_unit::SECONDE * 2) {
        this->fire(r);
        clock.restart();
    }
}

void game::Component::Enemy::fire(uwugine::Registery &r)
{
    auto &position = r.get_components<uwugine::Component::position>()[id];

    Fire fire(r, position.curent, 180, "p");
    fire.power = power;
    r.add_component(fire.id, std::move(fire));
}

void game::Component::Enemy::create(uwugine::Registery &r, EnemyProperties properties)
{
    power = properties.damage;

    id = r.spawn_entity();
    uwugine::Sprite sprite(uwugine::getTexture(properties.sprite_path),
        {{0, 0}, {static_cast<float>(properties.sprite_size.first), static_cast<float>(properties.sprite_size.second)}});
    uwugine::Component::hitbox hit = {
        uwugine::Rectangle(
            uwugine::Point2f{static_cast<float>(properties.spawn_position.first), static_cast<float>(properties.spawn_position.second)},
            uwugine::Point2f{static_cast<float>(properties.sprite_size.first * 2), static_cast<float>(properties.sprite_size.second * 2)}),
        0};

    sprite.setScale({2, 2});
    hit.setMsg("e," + std::to_string(id) + ",");
    r.add_component(id,
        uwugine::Component::position{
            uwugine::Point2f{static_cast<float>(properties.spawn_position.first), static_cast<float>(properties.spawn_position.second)},
            uwugine::Point2f{static_cast<float>(properties.spawn_position.first), static_cast<float>(properties.spawn_position.second)}});
    r.add_component(id, uwugine::Component::velocity{1, get_rad(180)});
    r.add_component(id, uwugine::Component::sprite{std::move(sprite), 1, {{getSheetFrames(properties.sprite_nb_frames, properties.sprite_size.first)}}});
    r.add_component(id, uwugine::Component::animation());
    r.add_component(id, uwugine::Clock());
    r.add_component(id, std::move(hit));
}

game::Component::Player::Player(uwugine::Registery &r, uwugine::Point2f pos) : AMob()
{
    id = r.spawn_entity();
    uwugine::Sprite sprite(uwugine::getTexture("./assets/sprites/r-typesheet42.gif"), {{0, 0}, {33, 17}});
    uwugine::Component::hitbox hit = {uwugine::Rectangle(uwugine::Point2f{0, 0}, uwugine::Point2f{33, 17}), 0};

    hit.setMsg("p," + std::to_string(id) + std::string(","));
    hit.setPosition({0, 0});
    r.add_component(id, uwugine::Component::position{{0, 0}, {0, 0}});
    r.add_component(id, uwugine::Component::velocity{0, 0});
    r.add_component(id, std::move(hit));
    r.add_component(id, uwugine::Component::controllable());
    r.add_component(id, uwugine::Clock());
    r.add_component(id, uwugine::Component::sprite{std::move(sprite), 1, {{getSheetFrames(5, 33)}}});
    r.add_component(id, uwugine::Component::animation());

    std::string line;
    std::ifstream myfile("./game/levels.txt");
    int p = 0;
    std::string delimiter = ":";

    if (!myfile.is_open())
        throw game::Exception("no game/levels.txt file");
    try {
        while (std::getline(myfile, line)) {
            p = line.find(delimiter);
            levels.insert({stoi(line.substr(0, p)), stof(line.substr(p + delimiter.length(), line.size() - 1))});
        }
    } catch (std::exception &e) {
        throw game::Exception("invalid levels.txt file");
    }
    myfile.close();
}

void game::Component::Player::move(uwugine::Registery &r)
{
    sf::Event event;

    auto &position = r.get_components<uwugine::Component::position>()[id];
    auto &velocity = r.get_components<uwugine::Component::velocity>()[id];
    auto &contr = r.get_components<uwugine::Component::controllable>()[id];
    velocity.speed = 0;

    if (is_colliding) {
        is_colliding = false;
        return;
    }
    while (!contr.empty()) {
        event = contr.top();
        if (event.type == sf::Event::Closed)
            r.win.close();
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Right:
                    if (position.curent.x < 400) {
                        velocity.angle = get_rad(0);
                        velocity.speed = 3;
                    }
                    break;
                case sf::Keyboard::Left:
                    if (position.curent.x > 0) {
                        velocity.angle = get_rad(180);
                        velocity.speed = 3;
                    }
                    break;
                case sf::Keyboard::Up:
                    if (position.curent.y > 0) {
                        velocity.angle = get_rad(270);
                        velocity.speed = 3;
                    }
                    break;
                case sf::Keyboard::Down:
                    if (position.curent.y < 400) {
                        velocity.angle = get_rad(90);
                        velocity.speed = 3;
                    }
                    break;
                default:
                    {
                        if (event.key.code == sf::Keyboard::Enter) {
                            auto &clock = r.get_components<uwugine::Clock>()[id];
                            if (clock.getElapsedTime() > uwugine::Time_unit::SECONDE * 0.2) {
                                fire(r);
                                if (clock.getElapsedTime() > uwugine::Time_unit::SECONDE * level && levels.count(level + 1)) {
                                    level += 1;
                                }
                                clock.restart();
                            }
                        } else {
                            velocity.speed = 0;
                            position.last = position.curent;
                        }
                    }
            }
        }
        contr.pop();
    }
}

void game::Component::Player::fire(uwugine::Registery &r)
{
    if (levels[level] > 5)
        levels[level] = 5;
    if (levels[level] <= 0)
        levels[level] = 1;
    auto &position = r.get_components<uwugine::Component::position>()[id];
    int angle = (90) / levels[level];
    int vel_angle = 22;

    if (levels[level] <= 1)
        vel_angle = 0;
    for (int i = 0; i < levels[level]; i++) {
        Fire fire(r, position.curent, 0, "e");
        auto &velocity = r.get_components<uwugine::Component::velocity>()[fire.id];
        velocity.angle = get_rad(vel_angle);
        vel_angle -= angle;
        if (vel_angle <= 0)
            vel_angle = 360 + vel_angle;
        fire.power = levels[level];
        r.add_component(fire.id, std::move(fire));
    }
    uwugine::Systems::update_sprite(r);
}