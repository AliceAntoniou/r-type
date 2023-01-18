/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Color
*/

#pragma once

namespace uwugine
{
    struct color_uint8 {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a = 255;
    };

    constexpr color_uint8 WHITE_COLOR = {255, 255, 255};
    constexpr color_uint8 BLACK_COLOR = {0, 0, 0};
} // namespace uwugine
