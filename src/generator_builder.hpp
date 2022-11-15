#ifndef GENERATOR_BUILDER_HPP
#define GENERATOR_BUILDER_HPP

#include "generators.hpp"

class GeneratorBuilder {
   public:
    // NOTE: ptrToGenerator is destroyed when this build function is called
    // TODO: consider using unique_ptr here instead for auto mem management
    static Generator* build(GENERATOR_TYPE genType, Generator* ptrToGenerator) {
        delete ptrToGenerator;
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