/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Window
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <memory>

namespace uwugine
{
    class Window;
    class Layer {
        public:
            Layer(void) noexcept = default;

            Layer(const Layer &) noexcept = default;
            Layer(Layer &&) noexcept = default;
            ~Layer(void) noexcept = default;

            Layer &operator=(const Layer &rhs) noexcept = default;
            Layer &operator=(Layer &&rhs) noexcept = default;

            void draw(Window &);
            void addDrawable(std::unique_ptr<sf::Drawable> &&);

        private:
            std::vector<std::unique_ptr<sf::Drawable>> to_draw;
    };
    class Window {
        public:
            Window(void) noexcept = delete;
            Window(unsigned int width, unsigned int height, const std::string &title) noexcept;

            Window(const Window &) noexcept = default;
            Window(Window &&) noexcept = default;
            ~Window(void) noexcept = default;

            Window &operator=(const Window &rhs) noexcept = default;
            Window &operator=(Window &&rhs) noexcept = default;

            void display(void);
            bool pollEvent(sf::Event &event);
            void draw(const sf::Drawable &);

            sf::RenderWindow &getHandle();
            /**
             * @return true Window is open
             * @return false Window is not open
             */
            bool isOpen(void) const;
            /**
             * @brief Close the window
             *
             */
            void close(void);
            void addDrawable(std::unique_ptr<sf::Drawable> &&, std::size_t layer);

        private:
            std::vector<Layer> layers;
            sf::RenderWindow win;
    };
}