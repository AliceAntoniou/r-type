/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Game
*/

#include "Game.hpp"
#include "Components.hpp"
#include "Systems.hpp"
#include "Errors.hpp"
#include "Obstacle.hpp"
#include "UwUgine.hpp"
#include "JSONParser.hpp"
#include "EnemyWaves.hpp"
#include <typeindex>
#include <iostream>
#include <fstream>
#include <string>

void game::Game::add_enemy()
{
    EnemyProperties enemy {
        "random",
        0,
        1,
        0,
        2,
        0,
        {100, 100},
        "./assets/sprites/r-typesheet3.gif",
        {16, 16},
        12,
    };
    Component::Enemy e;
    e.create(r, enemy);
    r.add_component(e.id, std::move(e));
}

void game::Game::add_map()
{
    JSONParser parser;
    parser.parse("./assets/map.json");
    auto map = parser.get_map();
    for (auto &obstacle : map) {
        Component::Obstacle o;
        o.create(r, obstacle);
        r.add_component(obstacle.id, std::move(o));
    }
}

void game::Game::launch_game()
{
    try {
        Component::Player player(r, uwugine::Point2f{300, 300});
        r.add_component(player.id, std::move(player));

        add_map();
        add_enemy();
        add_game_systems();

        Component::Fire fire(r, uwugine::Point2f{500, 500}, 0, "e");
        r.add_component(fire.id, std::move(fire));

        Component::Background background(r);
        r.add_component(background.id, std::move(background));

        int i = 0;
        while (r.win.isOpen() && clock.getElapsedTime() < uwugine::Time_unit::SECONDE * 60 && r.get_components<game::Component::Player>().size()) {
            r.run_systems();
            r.win.display();
        }
    } catch (game::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void game::Game::add_game_systems()
{
    r.add_system(Systems::waves_system);
    r.add_system(Systems::update_mobs);
}
