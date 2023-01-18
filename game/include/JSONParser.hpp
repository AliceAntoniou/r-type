//
// Created by natan on 05/11/2022.
//

#ifndef RTYPE_JSONPARSER_HPP
    #define RTYPE_JSONPARSER_HPP

#endif // RTYPE_JSONPARSER_HPP

#pragma once
#include "EnemyWaves.hpp"
#include "Map.hpp"
#include <nlohmann/json.hpp>

class JSONParser {
    private:
        nlohmann::json _json{};
        nlohmann::json j;

    public:
        JSONParser() = default;
        explicit JSONParser(std::string &filename);
        ~JSONParser() = default;

        void parse(std::string const &file_name);
        static std::vector<EnemyWave> get_waves(nlohmann::json json_data);
        static std::vector<ObstaclesProperties> get_map(nlohmann::json json_data);

        [[nodiscard]] std::vector<EnemyWave> get_waves() const;
        [[nodiscard]] std::vector<ObstaclesProperties> get_map() const;
        [[nodiscard]] nlohmann::json get_json() const;
};
