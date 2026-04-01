cmake_minimum_required(VERSION 3.20)
project(rock-paper-scissors-lizard-spock VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(include)

add_library(rock-paper-scissors-lizard-spock_lib src/game.cpp)
target_include_directories(rock-paper-scissors-lizard-spock_lib PUBLIC include)

add_executable(rock-paper-scissors-lizard-spock src/main.cpp)
target_link_libraries(rock-paper-scissors-lizard-spock PRIVATE rock-paper-scissors-lizard-spock_lib)
