/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Exception
*/

#include "Exception.hpp"

uwugine::Exception::Exception(const std::string &msg_) noexcept : msg("UwUgine: " + msg_) {}

const char *uwugine::Exception::what() const noexcept { return msg.c_str(); }

uwugine::ExceptInvalidPointer::ExceptInvalidPointer(void) noexcept : Exception("Invalid pointer") {}

uwugine::ExceptRegister::ExceptRegister(const std::string &msg_) noexcept : Exception("Registery: " + msg_) {}
