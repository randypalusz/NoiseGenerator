#include "generators.hpp"

#include <random>
#include <chrono>
#include <thread>

void SinglePassGenerator::run(Grid& grid) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 1);
    auto pixelInfo = grid.getPixelInfo();
    int i = 0;
    while (!m_shouldStop) {
        for (auto it = pixelInfo.begin(); it != pixelInfo.end(); it++, i++) {
            if (m_shouldStop) {
                break;
            }
            auto next = std::chrono::system_clock::now() + std::chrono::microseconds(5);
            sf::Color newColor = (distr(gen) == 0) ? sf::Color::Black : sf::Color::White;
            grid.setPixelColor(i, newColor);
            std::this_thread::sleep_until(next);
        }
        m_shouldStop = true;
    }
    printf("exiting run in SinglePassGenerator\n");
}