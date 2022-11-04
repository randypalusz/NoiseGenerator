#!/bin/bash

# github.com/conan-io/conan-center-index/issues/13772 to solve the pulse audio issue

mkdir -p build
cd build
conan install .. --build missing -pr default

while getopts dr opt; do
    case $opt in
        d ) echo "setting debug mode"; debug=1 ;;
        r ) echo "setting release mode"; release=1 ;;
        \? ) echo "${0##*/} [ -edr ]" >&2; exit 1 ;;
    esac
done
shift $((OPTIND-1))

if [[ "${debug}" -eq 1 ]]; then
    build_type="Debug"
fi

if [[ "${release}" -eq 1 ]]; then
    build_type="Release"
fi

cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=${build_type} -DCMAKE_CXX_COMPILER="/usr/bin/clang++"
cmake --build .