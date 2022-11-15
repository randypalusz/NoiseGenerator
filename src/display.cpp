#include "display.hpp"
#include "grid.hpp"

#include <iostream>
#include <SFML/System.hpp>
#include <thread>

#include "generators.hpp"
#include "generator_builder.hpp"
#include "frametime.hpp"

Display::~Display() {
    m_generator->abort();
    m_process.join();
    delete m_generator;
}

void Display::run(GENERATOR_TYPE genType) {
    Frametime ft{};

    m_generator = GeneratorBuilder::build(genType, m_generator);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        if (m_threadState == GENERATOR_STATE::NOT_STARTED) {
            m_process = std::thread(&Generator::generate, m_generator, std::ref(m_grid),
                                    std::ref(m_threadState));
            printf("Thread started\n");
        }

        ft.tick();

        m_window.clear();
        m_window.draw(m_grid.getVertexArray());
        m_window.display();
    }

    float avgFrameRate = ft.getFramerate();

    printf("Avg frame rate: %f\n", avgFrameRate);
}
