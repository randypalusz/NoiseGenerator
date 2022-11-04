#include "display.hpp"
#include "grid.hpp"

#include <iostream>
#include <SFML/System.hpp>
#include <thread>

#include "generators.hpp"

void Display::run() {
    sf::Clock clock{};
    sf::Int32 frameTimes[50] = {};
    int i = 0;

    // Generator* g;
    RandomGenerator g{};

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        if (m_threadState == GENERATOR_STATE::NOT_STARTED) {
            // Initialize the generator and start the run thread
            // g = new RandomGenerator();
            m_process = std::thread(&RandomGenerator::run, &g, std::ref(m_grid));
            m_threadState = GENERATOR_STATE::RUNNING;
            printf("Thread started\n");
        }

        sf::Int32 frameTime{clock.getElapsedTime().asMilliseconds()};
        frameTimes[i] = frameTime;
        clock.restart();

        i++;
        if (i > 50) i = 0;

        m_window.clear();
        m_window.draw(m_grid.getVertexArray());
        m_window.display();
    }

    g.abort();
    while (m_process.joinable()) {
        m_process.join();
    }
    m_threadState = GENERATOR_STATE::FINISHED;

    float avgFrameRate = 0.0f;
    for (int i = 0; i < 50; i++) {
        avgFrameRate += frameTimes[i];
    }
    avgFrameRate = 1000.0f / (avgFrameRate / 50);

    printf("Avg frame rate: %f\n", avgFrameRate);
}