#include "generator_builder.hpp"

const std::unordered_map<GENERATOR_TYPE, std::function<Generator*()>> GeneratorBuilder::ctorMap{
    {GENERATOR_TYPE::RANDOM_GENERATOR, []() { return new RandomGenerator(); }},
    {GENERATOR_TYPE::SINGLE_PASS_GENERATOR, []() { return new SinglePassGenerator(); }}};

const std::unordered_map<std::string, GENERATOR_TYPE> GeneratorBuilder::strToGeneratorMap{
    {"random", GENERATOR_TYPE::RANDOM_GENERATOR},
    {"single_pass", GENERATOR_TYPE::SINGLE_PASS_GENERATOR}};