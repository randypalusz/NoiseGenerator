cmake_minimum_required(VERSION 3.8)
project(2D_Graphics CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES
    src/main.cc
    src/display.cpp
    src/display.hpp
    src/grid.cpp
    src/grid.hpp
    src/generator_state.hpp
    src/generators.hpp
    src/random_generator.cpp
    src/single_pass_generator.cpp
    src/perlin_noise_generator.cpp
    src/generator_builder.cpp
    src/generator_builder.hpp
    src/util.hpp
)

add_executable(main ${SOURCES})
target_link_libraries(main ${CONAN_LIBS})




