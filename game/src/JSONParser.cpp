//
// Created by natan on 25/10/2022.
//

#include "JSONParser.hpp"
#include "EnemyWaves.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using json = nlohmann::json;

JSONParser::JSONParser(std::string &filename)
{
    parse(filename);
}

void JSONParser::parse(const std::string &file_name)
{
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening " << file_name << std::endl;
        throw std::runtime_error("Error opening " + file_name);
    }
    j = json::parse(file);
}

std::vector<EnemyWave> JSONParser::get_waves() const { return get_waves(j); }

std::vector<EnemyWave> JSONParser::get_waves(json json_data)
{
    std::vector<EnemyWave> waves;
    for (auto &wave : json_data["waves"]) {
        EnemyWave w;
        w.wave_name = wave["wave_name"];
        w.wave_id = wave["wave_id"];
        w.wave_duration = wave["wave_duration"];
        w.difficulty_index = wave["difficulty_index"];
        w.enemy_qty = wave["enemy_qty"];
        for (auto &enemy : wave["wave_enemies"]) {
            EnemyProperties e;
            e.enemy_name = enemy["enemy_name"];
            e.id = enemy["enemy_id"];
            e.health = enemy["enemy_health"];
            e.damage = enemy["enemy_damage"];
            e.speed = enemy["enemy_speed"];
            e.spawn_time = enemy["enemy_spawn_time"];
            e.spawn_position.first = enemy["enemy_spawn_location"]["x"];
            e.spawn_position.second = enemy["enemy_spawn_location"]["y"];
            e.sprite_path = enemy["enemy_sprite"];
            e.sprite_size.first = enemy["enemy_sprite_size"]["width"];
            e.sprite_size.second = enemy["enemy_sprite_size"]["height"];
            e.sprite_nb_frames = enemy["enemy_sprite_frames"];
            w.wave_enemies.push_back(e);
        }
        waves.push_back(w);
    }
    return waves;
}

std::vector<ObstaclesProperties> JSONParser::get_map() const { return get_map(j); }

std::vector<ObstaclesProperties> JSONParser::get_map(json json_data)
{
    Map m;
    auto &map = json_data["map"];
    m.map_name = map["map_name"];
    m.map_id = map["map_id"];
    m.obstacles_qty = map["obstacles_qty"];
    for (auto &obstacle : map["obstacles"]) {
        ObstaclesProperties o;
        o.name = obstacle["name"];
        o.id = obstacle["id"];
        o.speed = obstacle["speed"];
        o.spawn_time = obstacle["spawn_time"];
        o.sprite_path = obstacle["sprite"];
        o.sprite_size.first = obstacle["sprite_size"]["width"];
        o.sprite_size.second = obstacle["sprite_size"]["height"];
        o.sprite_nb_frames = obstacle["obstacles_sprite_frames"];
        o.x = obstacle["x"];
        o.y = obstacle["y"];
        o.scale = obstacle["scale"];
        m.map_obstacles.push_back(o);
    }
    return m.map_obstacles;
}

json JSONParser::get_json() const { return _json; }
