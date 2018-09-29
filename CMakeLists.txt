cmake_minimum_required(VERSION 2.8)

project(senseless_soccer2)

# --------------------------------------------------
# environment variables
# --------------------------------------------------
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# --------------------------------------------------
# include dirs
# --------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../gamelib2/lib)

# --------------------------------------------------
# compiler flags
# --------------------------------------------------
add_definitions(-std=c++11)

# --------------------------------------------------
# build files
# --------------------------------------------------
add_executable(senseless_soccer
  src/main.cpp
  src/player/player.cpp
  src/player/playerfactory.cpp
)

# --------------------------------------------------
# link libs
# --------------------------------------------------
target_link_libraries (senseless_soccer gamelib2)
target_link_libraries (senseless_soccer sfml-graphics-d)
target_link_libraries (senseless_soccer sfml-window-d)
target_link_libraries (senseless_soccer sfml-system-d)
target_link_libraries (senseless_soccer pthread)
