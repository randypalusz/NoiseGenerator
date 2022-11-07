#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <atomic>

#include "grid.hpp"

class Generator {
   public:
    virtual void run(Grid& grid) = 0;
    virtual void abort() { m_shouldStop = true; };
    virtual ~Generator(){};

   protected:
    std::atomic<bool> m_shouldStop{false};
    Generator(){};
};

class RandomGenerator : public Generator {
   public:
    RandomGenerator(){};
    virtual void run(Grid& grid) override;
};

class SinglePassGenerator : public Generator {
   public:
    SinglePassGenerator(){};
    virtual void run(Grid& grid) override;
};

#endif