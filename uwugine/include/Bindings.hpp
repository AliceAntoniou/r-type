/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Events
*/

#pragma once

#include "Point.hpp"
#include <stack>

#define SFML

#ifdef SFML
    #include <SFML/Graphics.hpp>
#endif
#ifdef SDL
    #include <SDL2/SDL_events.h>
#endif

namespace uwugine
{
#ifdef SFML
    using Event = sf::Event;
    using Keyboard = sf::Keyboard;
#endif
#ifdef SDL
    using Event = SDL_Event;
    using Keyboard = SDL_KeyCode;
#endif
} // namespace uwugine
