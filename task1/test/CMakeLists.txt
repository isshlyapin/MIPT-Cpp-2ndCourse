# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта для тестов
project(2QCache_Tests)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем исходные файлы для тестов
set(TEST_SOURCES
    src/test_main.cpp
    src/test_cache.cpp
    src/test_utils.cpp
)

# Создаем цель для тестов
add_executable(MyTests ${TEST_SOURCES})

# Указываем каталог для заголовочных файлов
target_include_directories(MyTests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test/include
)

set_target_properties(MyTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    OUTPUT_NAME test
    DEBUG_POSTFIX _debug
)

# Настройка GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Настройка spdlog через FetchContent
# FetchContent_Declare(
#   spdlog
#   GIT_REPOSITORY https://github.com/gabime/spdlog.git
#   GIT_TAG v1.10.0
# )
# FetchContent_MakeAvailable(spdlog)

# Линкуем GoogleTest с тестами
target_link_libraries(MyTests PRIVATE GTest::gtest GTest::gtest_main)

# Линкуем spdlog с тестами
# target_link_libraries(MyTests PRIVATE spdlog::spdlog)

# Опции компиляции для тестов в Debug режиме
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(MyTests PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wfloat-equal -Wunused -Wsign-conversion)
endif()
