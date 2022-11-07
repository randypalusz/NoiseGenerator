#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

#include "grid.hpp"
#include "generators.hpp"
#include "generator_state.hpp"

class Display {
   public:
    Display(float width, float height)
        : m_window(sf::VideoMode(width, height), "Title"), m_grid(100, 100, width){};
    void run();

   private:
    sf::RenderWindow m_window;
    Grid m_grid;
    Generator* m_generator;
    std::thread m_process;
    GENERATOR_STATE m_threadState = GENERATOR_STATE::NOT_STARTED;
};

#endif