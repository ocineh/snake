cmake_minimum_required(VERSION 3.11)
project(snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(C:/MinGWLib/include)

add_executable(snake main.cpp)
target_link_libraries(snake ${SDL2_LIBRARIES} -lmingw32 -mwindows)
add_definitions(-DSDL_MAIN_HANDLED)