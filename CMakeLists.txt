cmake_minimum_required(VERSION 2.8)

project(senseless_soccer)

# --------------------------------------------------
# environment variables
# --------------------------------------------------
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# --------------------------------------------------
# include dirs
# --------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../gamelib2/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.0/include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../gamelib2/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.0/Debug/lib)

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
  src/memory/playerfactory.cpp
  src/memory/ballfactory.cpp
  src/joysticker/sensicontroller.cpp
  src/joysticker/aftertouch.cpp
  src/team/team.cpp
  src/player/player.cpp
  src/player/states/state.cpp
  src/player/states/standing.cpp
  src/player/states/running.cpp
  src/ball/ball.cpp
  src/pitch/pitch.cpp
  src/player/locomotion/locomotionmanager.cpp
  src/player/locomotion/locomotion.cpp
  src/player/locomotion/stand.cpp
  src/player/locomotion/seek.cpp
  src/player/locomotion/pursue.cpp
  src/player/ai/brain.cpp
  src/player/ai/brainstate.cpp
  src/player/ai/attack/dribble.cpp
  src/player/ai/attack/receivepass.cpp
)

# --------------------------------------------------
# link libs
# --------------------------------------------------
target_link_libraries (senseless_soccer gamelib2)
target_link_libraries (senseless_soccer sfml-graphics-d)
target_link_libraries (senseless_soccer sfml-window-d)
target_link_libraries (senseless_soccer sfml-system-d)
target_link_libraries (senseless_soccer pthread)
target_link_libraries (senseless_soccer X11)
