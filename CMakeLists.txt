cmake_minimum_required(VERSION 3.11)
project(snake VERSION 0.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_executable(snake src/main.cpp src/snake.cpp src/snake.hpp src/game.cpp src/game.hpp)
add_definitions(-DSDL_MAIN_HANDLED)

IF (WIN32)
    include_directories(C:/MinGWLib/include)
ELSEIF(APPLE)
    include_directories(/usr/local/include)
ENDIF()

find_package(SDL2TTF REQUIRED)
include_directories(${SDL2TTF_INCLUDE_DIR})
target_link_libraries(snake ${SDL2TTF_LIBRARY})

find_package(SDL2 REQUIRED)
find_library(SDL2_LIBRARY NAME SDL2)
target_link_libraries(snake ${SDL2_LIBRARIES})