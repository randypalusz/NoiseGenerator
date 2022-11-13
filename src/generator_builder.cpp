#include "generator_builder.hpp"

#define gen_lambda(x) []() { return new x(); }

const std::unordered_map<GENERATOR_TYPE, std::function<Generator*()>> GeneratorBuilder::ctorMap{
    {GENERATOR_TYPE::RANDOM_GENERATOR, gen_lambda(RandomGenerator)},
    {GENERATOR_TYPE::SINGLE_PASS_GENERATOR, []() { return new SinglePassGenerator(); }},
    {GENERATOR_TYPE::PERLIN_NOISE_GENERATOR, []() { return new PerlinNoiseGenerator(); }}};

const std::unordered_map<std::string, GENERATOR_TYPE> GeneratorBuilder::strToGeneratorMap{
    {"random", GENERATOR_TYPE::RANDOM_GENERATOR},
    {"single_pass", GENERATOR_TYPE::SINGLE_PASS_GENERATOR},
    {"perlin", GENERATOR_TYPE::PERLIN_NOISE_GENERATOR}};