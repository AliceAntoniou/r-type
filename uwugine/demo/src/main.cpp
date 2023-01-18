/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** mainc
*/

#include "UwUgine.hpp"
#include <cmath>

using namespace uwugine;

static inline float get_rad(float a) { return M_PI * (a / 180); }

void init_map(Registery &r)
{
    Object<Component::sprite_vector> map{r, Component::sprite_vector(0)};
    auto &sprites = map.getComponent<Component::sprite_vector>();
    Texture &floor = getTexture("../uwugine/demo/assets/map.png");
    Sprite *s = nullptr;

    for (float x = 0; x < 15; x++) {
        for (float y = 0; y < 15; y++) {
            s = &sprites.emplace_back(Component::sprite{Sprite{floor, {{64, 64}, {16, 16}}}, 1}).sprite;
            s->setPosition({x * 64, y * 64});
            s->setScale({4, 4});
        }
    }
}

struct enemy_t {
        enum Type { updown, square };
        Type type;
        char direction = 0;
        Clock clock;
};

typedef char player_t;

void init_player(Registery &r)
{
    Object<Component::position, Component::controllable, Component::sprite, Component::animation, player_t> player(r,
        Component::position{{320, 320}}, Component::controllable(),
        Component::sprite{Sprite{getTexture("../uwugine/demo/assets/Enemy 15-6.png"), {{0, 0}, {32, 32}}}, 10,
            {{{{0, 0}, {32, 0}, {64, 0}}, {{0, 32}, {32, 32}, {64, 32}}, {{0, 64}, {32, 64}, {64, 64}}, {{0, 96}, {32, 96}, {64, 96}}},
                Time_unit::SECONDE / 4}},
        {0}, 0);
    Sprite &s = player.getComponent<Component::sprite>().sprite;

    s.setPosition(player.getComponent<Component::position>().curent);
    s.setScale({2, 2});
    static bool first_time = true;
    if (!first_time)
        return;
    r.add_system([](Registery &r) {
        for (Zipper_iterator<Component::controllable, Component::position, Component::animation, player_t> z(r); !z.is_end(); z++) {
            auto &c = z.get<Component::controllable>();
            auto &p = z.get<Component::position>();
            auto &a = z.get<Component::animation>();

            while (!c.empty()) {
                if (c.top().type == Event::KeyPressed) {
                    switch (c.top().key.code) {
                        case sf::Keyboard::Down:
                            p.curent.y += 64;
                            a.idx = 0;
                            a.refresh = true;
                            break;
                        case sf::Keyboard::Left:
                            p.curent.x -= 64;
                            a.idx = 1;
                            a.refresh = true;
                            break;
                        case sf::Keyboard::Up:
                            p.curent.y -= 64;
                            a.idx = 3;
                            a.refresh = true;
                            break;
                        case sf::Keyboard::Right:
                            p.curent.x += 64;
                            a.idx = 2;
                            a.refresh = true;
                            break;
                        default:
                            break;
                    }
                    for (Zipper_iterator<Component::position, entity_t, enemy_t> z2(r); !z2.is_end(); z2++) {
                        auto &enemy_pos = z2.get<Component::position>();
                        auto &enemy_idx = z2.get<entity_t>();

                        if (p.curent == enemy_pos.curent) {
                            r.kill_entity(enemy_idx);
                            p.curent = p.last;
                        }
                    }
                }
                c.pop();
            }
        }
    });
    first_time = false;
}

void init_enemy(Registery &r, const Point2i &pos, enemy_t::Type type)
{
    Object<Component::position, Component::sprite, Component::animation, enemy_t> player(r, Component::position{pos},
        Component::sprite{Sprite{getTexture(type == enemy_t::Type::updown ? "../uwugine/demo/assets/Enemy 15-5.png" : "../uwugine/demo/assets/Enemy 15-4.png"), {{0, 0}, {32, 32}}}, 5,
            {{{{0, 0}, {32, 0}, {64, 0}}}, Time_unit::SECONDE / 4}},
        {0}, {type});
    Sprite &s = player.getComponent<Component::sprite>().sprite;

    s.setPosition(player.getComponent<Component::position>().curent);
    s.setScale({2, 2});

    static bool first_time = true;
    if (!first_time)
        return;
    r.add_system([](Registery &r) {
        for (Zipper_iterator<Component::position, enemy_t> z(r); !z.is_end(); z++) {
            auto &p = z.get<Component::position>();
            auto &e = z.get<enemy_t>();

            if (e.clock.getElapsedTime() > Time_unit::SECONDE / 2) {
                switch (e.type) {
                    case enemy_t::Type::updown:
                        switch (e.direction) {
                            case 0:
                                p.curent.y += 64;
                                e.direction = 1;
                                break;
                            case 1:
                                p.curent.y -= 64;
                                e.direction = 0;
                                break;
                            default:
                                break;
                        }
                        break;
                    case enemy_t::Type::square:
                        switch (e.direction) {
                            case 0:
                                p.curent.y += 64;
                                e.direction = 1;
                                break;
                            case 1:
                                p.curent.x += 64;
                                e.direction = 2;
                                break;
                            case 2:
                                p.curent.y -= 64;
                                e.direction = 3;
                                break;
                            case 3:
                                p.curent.x -= 64;
                                e.direction = 0;
                                break;
                            default:
                                break;
                        }
                }
                for (Zipper_iterator<Component::position, player_t, entity_t> z2(r); !z2.is_end(); z2++) {
                    auto &player_pos = z2.get<Component::position>();
                    auto &player_idx = z2.get<entity_t>();

                    if (p.curent == player_pos.curent) {
                        r.kill_entity(player_idx);
                        init_player(r);
                        p.curent = p.last;
                        e.direction = !e.direction;
                    }
                }
                e.clock.restart();
            }
        }
    });
    first_time = false;
}

int main(void)
{
    try {
        Registery r({750, 750}, "Demo");
        init_map(r);
        init_player(r);
        init_enemy(r, {64, 64}, enemy_t::updown);
        init_enemy(r, {128, 192}, enemy_t::updown);
        init_enemy(r, {512, 256}, enemy_t::square);

        while (r.win.isOpen()) {
            r.run_systems();
            r.win.display();
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
