#!/usr/bin/bash

conan config install https://github.com/isshlyapin/conan_config.git
conan install . --output-folder=build --build=missing -s build_type=Release -pr:b gcc13 -pr:h gcc13
cmake --preset conan-release
cmake --build --preset conan-release
