#ifndef GENERATOR_BUILDER_HPP
#define GENERATOR_BUILDER_HPP

#include "generators.hpp"

// TODO: have the build method take in a pointer to the generator itself so that
// this class can manage the memory allocated for the generator
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