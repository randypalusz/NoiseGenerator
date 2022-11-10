#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <atomic>
#include <functional>
#include <unordered_map>
#include <string>

#include "grid.hpp"
#include "generator_state.hpp"

enum GENERATOR_TYPE { RANDOM_GENERATOR, SINGLE_PASS_GENERATOR, PERLIN_NOISE_GENERATOR, NONE };

class Generator {
   public:
    void generate(Grid& grid, GENERATOR_STATE& state) {
        state = GENERATOR_STATE::RUNNING;
        this->run(grid);
        state = GENERATOR_STATE::FINISHED;
        grid.writeToImage(m_name);
    }
    virtual void abort() { m_shouldStop = true; };
    virtual ~Generator(){};

   protected:
    Generator(){};
    virtual void run(Grid& grid) = 0;
    std::atomic<bool> m_shouldStop{false};
    std::string m_name{"PLACEHOLDER:NAME_UNSET"};
};

class RandomGenerator : public Generator {
   public:
    RandomGenerator() { m_name = "Random"; };

   protected:
    virtual void run(Grid& grid) override;
};

class SinglePassGenerator : public Generator {
   public:
    SinglePassGenerator() { m_name = "SinglePass"; };

   protected:
    virtual void run(Grid& grid) override;
};

class PerlinNoiseGenerator : public Generator {
   public:
    PerlinNoiseGenerator() {
        m_name = "Perlin";
        generatePermutationArray();
    };

   protected:
    virtual void run(Grid& grid) override;

   private:
    inline unsigned int inc(unsigned int x) { return (x + 1) & 255; }
    inline double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
    inline double lerp(double a, double b, double x) { return a + x * (b - a); }
    double grad(unsigned int hash, double x, double y, double z);
    double noise(double x, double y, double z);
    void generatePermutationArray();
    unsigned int permutation[512];
    ;
};

#endif