#include <iostream>
#include <string>

#include "generators.hpp"
#include "display.hpp"

int main(int argc, char** argv) {
    std::string input{};
    if (argc == 2) {
        input = std::string(argv[1]);
    }
    GENERATOR_TYPE genType = GeneratorBuilder::strToEnum(input);
    Display d{600.0f, 600.0f};
    d.run(genType);
    return 0;
}