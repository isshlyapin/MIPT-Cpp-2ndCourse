cmake_minimum_required(VERSION 3.10)

project(Cache VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
)


#--------------------------------------------------------------------
#                            2QCache
#--------------------------------------------------------------------
add_executable(2QCache ${SOURCES})

target_compile_definitions(2QCache PUBLIC MY_CACHE_2Q)

target_include_directories(2QCache PRIVATE ${PROJECT_INCLUDE_DIR})

set_target_properties(2QCache PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    OUTPUT_NAME cache_2q
    DEBUG_POSTFIX _debug
)
#--------------------------------------------------------------------


#--------------------------------------------------------------------
#                            BeladyCache
#--------------------------------------------------------------------
add_executable(BeladyCache ${SOURCES})

target_compile_definitions(BeladyCache PUBLIC MY_CACHE_BELADY)

target_include_directories(BeladyCache PRIVATE ${PROJECT_INCLUDE_DIR})

set_target_properties(BeladyCache PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    OUTPUT_NAME cache_belady
    DEBUG_POSTFIX _debug
)
#--------------------------------------------------------------------

#--------------------------------------------------------------------
#                           Подключаем тесты
#--------------------------------------------------------------------
option(ENABLE_TESTING "Enable building of tests" OFF)
if(ENABLE_TESTING)
    add_subdirectory(test)
endif()
#--------------------------------------------------------------------
