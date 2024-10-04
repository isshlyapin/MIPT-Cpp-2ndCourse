# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта
project(2QCache VERSION 1.0)

# Включаем экспорт команд компиляции
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем каталог для include
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Добавляем цель для основной программы
set(SOURCES
    src/main.cpp
)

add_executable(2QCache ${SOURCES})

# Указываем директории для заголовочных файлов
target_include_directories(2QCache PRIVATE ${PROJECT_INCLUDE_DIR})

set_target_properties(2QCache PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    OUTPUT_NAME cache
    DEBUG_POSTFIX _debug
)

# Настройка spdlog через FetchContent
# include(FetchContent)
# FetchContent_Declare(
#   spdlog
#   GIT_REPOSITORY https://github.com/gabime/spdlog.git
#   GIT_TAG v1.10.0
# )
# FetchContent_MakeAvailable(spdlog)

# Линкуем spdlog с основной целью
# target_link_libraries(2QCache PRIVATE spdlog::spdlog)

# Указываем настройки компиляции для Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(2QCache PRIVATE -DMYLOG_DEBUG)
    target_compile_options(2QCache PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wfloat-equal -Wunused -Wsign-conversion)
endif()

# Подключаем тесты
add_subdirectory(test)
