cmake_minimum_required(VERSION 3.24)
project(sw_battle_test)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
add_executable(sw_battle_test ${SOURCES})

target_include_directories(sw_battle_test PUBLIC src/)

set(SCENARIO_FILE ${CMAKE_SOURCE_DIR}/scenario.txt)

set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(
    OUTPUT ${OUTPUT_DIR}/scenario.txt
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SCENARIO_FILE} ${OUTPUT_DIR}/scenario.txt
    DEPENDS ${SCENARIO_FILE}
    COMMENT "Copying scenario.txt to build directory"
)

add_custom_target(copy_resources ALL
    DEPENDS ${OUTPUT_DIR}/scenario.txt
)

add_dependencies(sw_battle_test copy_resources)
