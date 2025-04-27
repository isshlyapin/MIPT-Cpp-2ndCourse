cmake_minimum_required(VERSION 3.10)

project(Cache_Tests)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TEST_SOURCES
    src/test_main.cpp
    src/test_cache.cpp
    src/test_utils.cpp
    src/module_tests.cpp
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
target_link_libraries(MyTests gtest::gtest)
#--------------------------------------------------------------------


#--------------------------------------------------------------------
# Функция для установки опций компилятора для каждой конфигурации
#--------------------------------------------------------------------
function(add_sanitizer_test target sanitizer_name san_flags)
    add_executable(${target}_${sanitizer_name} ${TEST_SOURCES})
    target_compile_options(${target}_${sanitizer_name} PRIVATE ${san_flags} ${MY_DEBUG_FLAGS})
    target_link_options(${target}_${sanitizer_name} PRIVATE ${san_flags} ${MY_DEBUG_FLAGS})
    target_link_libraries(${target}_${sanitizer_name} gtest::gtest)
    target_include_directories(${target}_${sanitizer_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/test/include
    )
    set_target_properties(${target}_${sanitizer_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        OUTPUT_NAME ${target}_${sanitizer_name}
        DEBUG_POSTFIX _debug
    )

    add_test(NAME ${target}_${sanitizer_name} COMMAND ${target}_${sanitizer_name})
endfunction()
#--------------------------------------------------------------------