/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Window
*/

#include "Window.hpp"
#include "Exception.hpp"
#include <iostream>
void uwugine::Layer::draw(Window &win)
{
    for (const auto &obj : to_draw) {
        win.draw(*obj);
    }
}

void uwugine::Layer::addDrawable(std::unique_ptr<sf::Drawable> &&d)
{
    // if (!d)
    //     throw ExceptInvalidPointer();
    to_draw.push_back(std::move(d));
}

uwugine::Window::Window(unsigned int width, unsigned int height, const std::string &title) noexcept
    : win(sf::VideoMode{width, height}, title)
{
    win.setFramerateLimit(60);
}

void uwugine::Window::display(void)
{
    win.clear(sf::Color::Black);
    for (auto &layer : layers) {
        layer.draw(*this);
    }
    layers.clear();
    win.display();
}

bool uwugine::Window::pollEvent(sf::Event &event) { return win.pollEvent(event); }

sf::RenderWindow &uwugine::Window::getHandle(void) { return win; }

bool uwugine::Window::isOpen(void) const { return win.isOpen(); }

void uwugine::Window::close(void) { win.close(); }

void uwugine::Window::addDrawable(std::unique_ptr<sf::Drawable> &&d, std::size_t layer)
{
    // if (!d)
    //     throw ExceptInvalidPointer();
    while (layers.size() <= layer) {
        layers.emplace_back();
    }
    layers[layer].addDrawable(std::move(d));
}

void uwugine::Window::draw(const sf::Drawable &obj) { win.draw(obj); }
