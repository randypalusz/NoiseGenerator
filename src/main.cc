#include <iostream>
#include <string>

#include "generator_builder.hpp"
#include "display.hpp"

int main(int argc, char** argv) {
    std::string input{};
    if (argc == 2) {
        input = std::string(argv[1]);
    }
    GENERATOR_TYPE genType = GeneratorBuilder::strToEnum(input);
    Display d{1000.0f, 600.0f, 50};
    d.run(genType);
    return 0;
}