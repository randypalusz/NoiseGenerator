#include "frametime.hpp"

void Frametime::tick() {
    sf::Int32 frameTime{m_clock.getElapsedTime().asMilliseconds()};
    m_frameTimes[m_idx] = frameTime;
    m_clock.restart();

    m_idx++;
    if (m_idx >= NUM_SAMPLES) m_idx = 0;
}

float Frametime::getFramerate() {
    float avgFrameRate = 0.0f;
    for (size_t i = 0; i < NUM_SAMPLES; i++) {
        avgFrameRate += m_frameTimes[i];
    }
    return 1000.0f / (avgFrameRate / NUM_SAMPLES);
}