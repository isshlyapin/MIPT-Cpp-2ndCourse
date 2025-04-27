#!/usr/bin/bash

 
uv run conan config install https://github.com/isshlyapin/conan_config.git 
uv run conan build . --build=missing -s build_type=Release -pr:b gcc13 -pr:h gcc13