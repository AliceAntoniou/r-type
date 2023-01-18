/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Exception
*/

#pragma once

#include <exception>
#include <string>

namespace uwugine
{
    class Exception : std::exception {
        public:
            Exception(void) noexcept = default;
            Exception(const std::string &msg) noexcept;

            Exception(const Exception &) noexcept = default;
            Exception(Exception &&) noexcept = default;
            ~Exception(void) noexcept override = default;

            Exception &operator=(const Exception &rhs) noexcept = default;
            Exception &operator=(Exception &&rhs) noexcept = default;

            const char *what() const noexcept final;

        private:
            std::string msg = "UwUgine: error";
    };

    class ExceptInvalidPointer : public Exception {
        public:
            ExceptInvalidPointer(void) noexcept;
    };

    class ExceptRegister : public Exception {
        public:
            ExceptRegister(void) noexcept = delete;
            ExceptRegister(const std::string &msg) noexcept;
    };

    template <typename type> class ExceptComponantNotFound : public ExceptRegister {
        public:
            ExceptComponantNotFound(void) noexcept
                : ExceptRegister(std::string("Componant <") + typeid(type).name() + "> is not registered")
            {
            }
    };
} // namespace uwugine
