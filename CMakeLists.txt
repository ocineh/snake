cmake_minimum_required(VERSION 3.11)
project(snake VERSION 0.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
IF (WIN32)
include_directories(C:/MinGWLib/include)
ELSE()
include_directories(/usr/local/include)
ENDIF()

add_executable(snake src/main.cpp src/snake.cpp src/snake.hpp src/game.cpp src/game.hpp)
target_link_libraries(snake ${SDL2_LIBRARIES})
add_definitions(-DSDL_MAIN_HANDLED)