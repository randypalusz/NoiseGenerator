#ifndef __FRAMETIME_H__
#define __FRAMETIME_H__

#include <stdlib.h>
#include <SFML/System.hpp>

class Frametime {
   public:
    Frametime() { m_clock.restart(); };
    void tick();
    float getFramerate();

   private:
    sf::Clock m_clock{};
    static const size_t NUM_SAMPLES = 50;
    sf::Int32 m_frameTimes[NUM_SAMPLES];
    size_t m_idx = 0;
};

#endif  // __FRAMETIME_H__