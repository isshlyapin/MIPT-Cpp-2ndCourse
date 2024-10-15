cmake_minimum_required(VERSION 3.10)

project(Cache_Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TEST_SOURCES
    src/test_main.cpp
    src/test_cache.cpp
    src/test_utils.cpp
)


#--------------------------------------------------------------------
#                            MyTests
#--------------------------------------------------------------------
add_executable(MyTests ${TEST_SOURCES})

target_include_directories(MyTests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test/include
)

set_target_properties(MyTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    OUTPUT_NAME test
    DEBUG_POSTFIX _debug
)
#--------------------------------------------------------------------


#--------------------------------------------------------------------
#                            GTest
#--------------------------------------------------------------------
find_package(GTest REQUIRED)
target_link_libraries(MyTests PRIVATE GTest::gtest GTest::gtest_main)
#--------------------------------------------------------------------

#--------------------------------------------------------------------
#             Указываем настройки компиляции для Debug
#--------------------------------------------------------------------
include(${CMAKE_SOURCE_DIR}/debug_config.cmake)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(MyTests PRIVATE ${MY_DEBUG_FLAGS})
    target_link_options   (MyTests PRIVATE ${MY_DEBUG_FLAGS})
endif()
#--------------------------------------------------------------------
