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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.0/include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../gamelib2/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.0/Release/lib)

# --------------------------------------------------
# compiler flags
# --------------------------------------------------
add_definitions(-std=c++14)

# --------------------------------------------------
# build files
# --------------------------------------------------
add_executable(senseless_soccer
  src/main.cpp
  src/metrics/metrics.cpp
  src/player/player.cpp
  src/player/states/state.cpp
  src/player/states/stand.cpp
  src/player/states/run.cpp
  src/player/playerfactory.cpp
  src/ball/ball.cpp
  src/ball/ball_factory.cpp
  src/pitch/pitch.cpp
)

# --------------------------------------------------
# link libs
# --------------------------------------------------
target_link_libraries (senseless_soccer gamelib2)
target_link_libraries (senseless_soccer sfml-graphics)
target_link_libraries (senseless_soccer sfml-window)
target_link_libraries (senseless_soccer sfml-system)
target_link_libraries (senseless_soccer pthread)
target_link_libraries (senseless_soccer X11)
