/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Systems
*/

#include "Basic_Componants.hpp"
#include "Bindings.hpp"
#include "Registery.hpp"
#include "Zipper_iterator.hpp"
#include <cmath>

namespace uwugine::Systems
{
    void update_velocity(Registery &r)
    {
        for (Zipper_iterator<Component::position, Component::velocity> z(r); !z.is_end(); z++) {
            auto &pos = z.get<Component::position>();
            auto &v = z.get<Component::velocity>();

            v.speed = sqrt(pow(pos.curent.x - pos.last.x, 2) + pow(pos.curent.y - pos.last.y, 2));
            v.angle = atan2(pos.curent.y - pos.last.y, pos.curent.x - pos.last.x);
        }
    }

    void update_pos(Registery &r)
    {
        for (Zipper_iterator<Component::position> z(r); !z.is_end(); z++) {
            auto &pos = z.get<Component::position>();

            pos.last = pos.curent;
        }
    }

    void move(Registery &r)
    {
        for (Zipper_iterator<Component::position, Component::velocity> z(r); !z.is_end(); z++) {
            auto &pos = z.get<Component::position>();
            auto &v = z.get<Component::velocity>();

            pos.curent += Point2f{static_cast<float>(v.speed * cos(v.angle)), static_cast<float>(v.speed * sin(v.angle))};
        }
    }

    void gravity(Registery &r)
    {
        for (Zipper_iterator<Component::position, Component::gravity> z(r); !z.is_end(); z++) {
            auto &g = z.get<Component::gravity>();
            auto &pos = z.get<Component::position>();

            pos.curent.y += g;
        }
    }

    void anim_sprite(Registery &r)
    {
        for (Zipper_iterator<Component::sprite, Component::animation> z(r); !z.is_end(); z++) {
            auto &s = z.get<Component::sprite>();
            auto &a = z.get<Component::animation>();

            if (!s.animation.frames_pos.empty() && (a.refresh || s.animation.clock.getElapsedTime() >= s.animation.frame_duration)) {
                s.animation.curent_frame++;
                if (s.animation.frames_pos[a.idx].size() <= s.animation.curent_frame)
                    s.animation.curent_frame = 0;
                s.sprite.setTextureRect({s.animation.frames_pos[a.idx][s.animation.curent_frame], s.sprite.getTextureRect().getSize()});
                s.animation.clock.restart();
                a.refresh = false;
            }
        }
        for (Zipper_iterator<Component::sprite_vector, Component::animation> z(r); !z.is_end(); z++) {
            auto &vector = z.get<Component::sprite_vector>();
            auto &a = z.get<Component::animation>();

            for (auto &&s : vector) {
                if (!s.animation.frames_pos.empty() && (a.refresh || s.animation.clock.getElapsedTime() >= s.animation.frame_duration)) {
                    s.animation.curent_frame++;
                    if (s.animation.frames_pos.size() - 1 == s.animation.curent_frame)
                        s.animation.curent_frame = 0;
                    s.sprite.setTextureRect({s.animation.frames_pos[a.idx][s.animation.curent_frame], s.sprite.getTextureRect().getSize()});
                    s.animation.clock.restart();
                }
                a.refresh = false;
            }
        }
    }

    void update_sprite(Registery &r)
    {
        for (Zipper_iterator<Component::sprite, Component::position> z(r); !z.is_end(); z++) {
            auto &s = z.get<Component::sprite>();
            auto &pos = z.get<Component::position>();

            s.sprite.setPosition(pos.curent);
        }
        for (Zipper_iterator<Component::sprite_vector, Component::position> z(r); !z.is_end(); z++) {
            auto &vector = z.get<Component::sprite_vector>();
            auto &pos = z.get<Component::position>();

            for (auto &&s : vector) {
                if (pos.curent != pos.last)
                    s.sprite.setPosition(s.sprite.getPosition() + (pos.last - pos.curent));
            }
        }
    }

    void draw_sprite(Registery &r)
    {
        for (Zipper_iterator<Component::sprite> z(r); !z.is_end(); z++) {
            auto &s = z.get<Component::sprite>();

            if (s.to_draw)
                r.win.addDrawable(s.sprite.getDrawable(), s.layer);
        }
        for (Zipper_iterator<Component::sprite_vector> z(r); !z.is_end(); z++) {
            auto &vector = z.get<Component::sprite_vector>();

            for (auto &&s : vector) {
                if (s.to_draw)
                    r.win.addDrawable(s.sprite.getDrawable(), s.layer);
            }
        }
    }

    void update_text(Registery &r)
    {
        for (Zipper_iterator<Component::position, Component::text> z(r); !z.is_end(); z++) {
            auto &t = z.get<Component::text>();
            auto &pos = z.get<Component::position>();

            t.txt.setPosition(pos.curent);
        }
        for (Zipper_iterator<Component::text_vector, Component::position> z(r); !z.is_end(); z++) {
            auto &vector = z.get<Component::text_vector>();
            auto &pos = z.get<Component::position>();

            for (auto &&t : vector) {
                t.txt.setPosition(t.txt.getPosition() + (pos.last - pos.curent));
            }
        }
    }

    void draw_text(Registery &r)
    {
        for (Zipper_iterator<Component::text> z(r); !z.is_end(); z++) {
            auto &t = z.get<Component::text>();

            if (t.to_draw)
                r.win.addDrawable(t.txt.getDrawable(), t.layer);
        }
        for (Zipper_iterator<Component::text_vector> z(r); !z.is_end(); z++) {
            auto &vector = z.get<Component::text_vector>();

            for (auto &&t : vector) {
                if (t.to_draw)
                    r.win.addDrawable(t.txt.getDrawable(), t.layer);
            }
        }
    }

    void update_hitbox_colide(Registery &r)
    {
        for (Zipper_iterator<Component::hitbox> z(r); !z.is_end(); z++) {
            auto &me = z.get<Component::hitbox>();
            for (Zipper_iterator<Component::hitbox> y(r); !y.is_end(); y++) {
                auto &other = y.get<Component::hitbox>();
                if (me.isColiding(other)) {
                    other.onColide(r, me.getMsg());
                }
            }
        }
    }

    void update_hitbox_pos(Registery &r)
    {
        for (Zipper_iterator<Component::position, Component::hitbox> z(r); !z.is_end(); z++) {
            auto &hitbox = z.get<Component::hitbox>();
            auto &pos = z.get<Component::position>();

            hitbox.setPosition(pos.curent);
        }
    }

    void update_controlable(Registery &r)
    {
        Event e;

        while (r.win.pollEvent(e)) {
            if (e.type == Event::Closed)
                r.win.close();
            for (Zipper_iterator<Component::controllable> z(r); !z.is_end(); z++) {
                auto &c = z.get<Component::controllable>();

                c.push(e);
            }
        }
    }

    void check_multiplayer(Registery &r)
    {
        Client &cli = r.cli;
        package p;

        if (!cli.is_connected())
            return;
        if (cli.is_host()) {
            for (Zipper_iterator<Component::multiplayer_id, Component::position, Component::velocity> z(r); !z.is_end(); z++) {
                p.id = z.get<Component::multiplayer_id>();
                p.pos = z.get<Component::position>();
                p.v = z.get<Component::velocity>();
                cli.send(p);
            }
            return;
        }
        while (cli.listen(p)) {
            Zipper_iterator<Component::multiplayer_id, Component::position, Component::velocity> z(r);

            while (!z.is_end()) {
                if (p.id != z.get<Component::multiplayer_id>()) {
                    z++;
                    continue;
                }
                z.get<Component::position>() = p.pos;
                z.get<Component::velocity>() = p.v;
                z++;
            }
        }
    }
}
