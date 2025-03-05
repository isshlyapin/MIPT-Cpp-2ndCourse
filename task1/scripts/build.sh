#!/usr/bin/bash

set -x

conan install . --output-folder=build --build=missing --settings=build_type=Release -pr gcc-13
cmake --preset conan-release
cmake --build --preset conan-release
