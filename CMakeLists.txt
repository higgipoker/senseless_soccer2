cmake_minimum_required(VERSION 2.6)

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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../imgui-sfml)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../gamelib2/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.0/Release/lib)

# --------------------------------------------------
# compiler flags
# --------------------------------------------------
add_definitions(-std=c++17)
#add_definitions(-fsanitize=address)

# --------------------------------------------------
# linker flags
# --------------------------------------------------
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

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
    src/team/state.cpp
    src/team/enterpitch.cpp
    src/team/lineup.cpp
    src/team/defend.cpp
    src/team/kit.cpp
    src/team/tactics/formation.cpp
    src/team/tactics/position.cpp
    src/match/match.cpp
    src/match/state.cpp
    src/match/play.cpp
    src/match/enterpitch.cpp
    src/match/lineup.cpp
    src/match/kickoff.cpp
    src/match/goalkick.cpp
    src/match/throwin.cpp
    src/match/corner.cpp
    src/match/freekick.cpp
    src/player/player.cpp
    src/player/states/state.cpp
    src/player/states/standing.cpp
    src/player/states/running.cpp
    src/player/states/sliding.cpp
    src/player/states/jumping.cpp
    src/ball/ball.cpp
    src/pitch/pitch.cpp
    src/pitch/pitchwidget.cpp
    src/player/locomotion/locomotionmanager.cpp
    src/player/locomotion/locomotion.cpp
    src/player/locomotion/stand.cpp
    src/player/locomotion/seek.cpp
    src/player/locomotion/head.cpp
    src/player/locomotion/pursue.cpp
    src/player/locomotion/slide.cpp
    src/player/ai/brain.cpp
    src/player/ai/brainstate.cpp
    src/player/ai/idle.cpp
    src/player/ai/retrieve.cpp
    src/player/ai/jump.cpp
    src/player/ai/goto.cpp
    src/player/ai/attack/dribble.cpp
    src/player/ai/attack/pass.cpp
    src/player/ai/attack/receivepass.cpp
    src/player/ai/attack/shoot.cpp
    src/player/ai/defend/slide.cpp
    src/player/ai/defend/cover.cpp
    src/debug/diagnostics.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_demo.cpp
    src/imgui/imgui-SFML.cpp
)

# --------------------------------------------------
# link libs
# --------------------------------------------------

target_link_libraries (senseless_soccer gamelib2)
target_link_libraries (senseless_soccer sfml-graphics)
target_link_libraries (senseless_soccer sfml-window)
target_link_libraries (senseless_soccer sfml-system)
target_link_libraries (senseless_soccer stdc++fs)
target_link_libraries (senseless_soccer GL)
