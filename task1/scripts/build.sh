#!/usr/bin/bash

conan profile detect
conan install . --output-folder=build --build=missing --settings=build_type=Release
cmake --preset conan-release
cmake --build --preset conan-release
