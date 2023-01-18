/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#pragma once

#include "Multi_Components.hpp"
#include <iostream>
#include <string>

namespace uwugine
{
    struct package {
            size_t id;
            Component::position pos;
            Component::velocity v;
    };

    class Client {
            using fd_t = int;

        public:
            Client(void) noexcept = default;

            Client(const Client &) noexcept = default;
            Client(Client &&) noexcept = default;
            ~Client(void) noexcept = default;

            Client &operator=(const Client &) noexcept = default;
            Client &operator=(Client &&) noexcept = default;

            bool is_connected(void);
            bool connect_to(const std::string &adress);
            bool is_host(void);

            bool listen(package &);
            void send(const package &);

        private:
            bool connected = false;
            bool host = true;
            fd_t socket;
            std::string adress;
    };
} // namespace uwugine
