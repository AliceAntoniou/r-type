
/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** errors
*/

#pragma once

#include <exception>
#include <string>

namespace game
{
    class Exception : public std::exception {
        public:
            Exception(std::string const &message) : _message(message){};
            const char *what() const noexcept override { return (_message.c_str()); };

        private:
            std::string _message;
    };
}