#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <atomic>
#include <functional>
#include <unordered_map>
#include <string>

#include "grid.hpp"
#include "generator_state.hpp"

enum GENERATOR_TYPE { RANDOM_GENERATOR, SINGLE_PASS_GENERATOR, NONE };

class Generator {
   public:
    void generate(Grid& grid, GENERATOR_STATE& state) {
        state = GENERATOR_STATE::RUNNING;
        this->run(grid);
        state = GENERATOR_STATE::FINISHED;
    }
    virtual void abort() { m_shouldStop = true; };
    virtual ~Generator(){};

   protected:
    Generator(){};
    virtual void run(Grid& grid) = 0;
    std::atomic<bool> m_shouldStop{false};
};

class RandomGenerator : public Generator {
   public:
    RandomGenerator(){};

   protected:
    virtual void run(Grid& grid) override;
};

class SinglePassGenerator : public Generator {
   public:
    SinglePassGenerator(){};

   protected:
    virtual void run(Grid& grid) override;
};

// TODO: put this in its own hpp file
class GeneratorBuilder {
   public:
    static Generator* build(GENERATOR_TYPE genType) {
        return GeneratorBuilder::ctorMap.at(genType)();
    };
    static GENERATOR_TYPE strToEnum(const std::string& str) {
        try {
            return GeneratorBuilder::strToGeneratorMap.at(str);
        } catch (const std::exception& e) {
            return GENERATOR_TYPE::RANDOM_GENERATOR;
        }
    }

   private:
    static const std::unordered_map<GENERATOR_TYPE, std::function<Generator*()>> ctorMap;
    static const std::unordered_map<std::string, GENERATOR_TYPE> strToGeneratorMap;
};

#endif