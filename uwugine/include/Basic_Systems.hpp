/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Basic_Systems
*/

#pragma once

#include "Registery.hpp"

namespace uwugine::Systems
{
    void update_velocity(Registery &);
    void update_pos(Registery &r);
    void move(Registery &r);
    void gravity(Registery &r);
    void update_sprite(Registery &r);
    void anim_sprite(Registery &r);
    void update_text(Registery &r);
    void update_hitbox_colide(Registery &r);
    void update_hitbox_pos(Registery &r);
    void update_controlable(Registery &r);
    void draw_sprite(Registery &r);
    void draw_text(Registery &r);
    void check_multiplayer(Registery &r);
}
