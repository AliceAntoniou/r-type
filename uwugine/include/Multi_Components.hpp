/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Multi_Components
*/

#pragma once

#include "Point.hpp"

namespace uwugine::Component
{
    struct position {
            Point2f curent;
            Point2f last = curent;
    };
    struct velocity {
            float speed;
            float angle;
    };
    typedef unsigned long multiplayer_id;
}