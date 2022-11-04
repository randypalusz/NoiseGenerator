#include "generators.hpp"

#include <random>
#include <chrono>
#include <thread>

void RandomGenerator::run(Grid& grid) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, grid.getPixels().m_pixels.size() - 1);
    while (!m_shouldStop) {
        // do stuff
        int idx = distr(gen);
        auto next = std::chrono::system_clock::now() + std::chrono::milliseconds(1);
        sf::Color newColor =
            (grid.getPixelColor(idx) == sf::Color::White) ? sf::Color::Black : sf::Color::White;
        grid.setPixelColor(idx, newColor);
        std::this_thread::sleep_until(next);
    }
    printf("exiting run in RandomGenerator\n");
}
