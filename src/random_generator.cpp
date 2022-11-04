#include "generators.hpp"

#include <random>

void RandomGenerator::run(Grid& grid) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, grid.getPixels().m_pixels.size()-1);
    while (!m_shouldStop) {
        // do stuff
        int idx = distr(gen);
        sf::Color newColor = (grid.getPixelColor(idx) == sf::Color::White) ? sf::Color::Black : sf::Color::White;
        grid.setPixelColor(idx, newColor);
    }
    printf("exiting run in RandomGenerator\n");
}
