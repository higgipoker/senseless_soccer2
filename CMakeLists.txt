cmake_minimum_required(VERSION 2.6)

project(senseless_soccer)

# --------------------------------------------------
# environment variables
# --------------------------------------------------
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

# --------------------------------------------------
# include dirs
# --------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

# --------------------------------------------------
# compiler flags
# --------------------------------------------------
if (WIN32)
    add_definitions(-std:c++latest)
endif (WIN32)

if (UNIX)
    add_definitions(-std=c++17)
endif (UNIX)
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
    src/joysticker/sensicontroller.cpp
    src/joysticker/aftertouch.cpp
    src/team/team.cpp
    src/team/team_state.cpp
    src/team/team_enterpitch.cpp
    src/team/team_lineup.cpp
    src/team/defend.cpp
    src/team/team_idle.cpp
    src/team/kit.cpp
    src/team/tactics/formation.cpp
    src/team/tactics/position.cpp
    src/team/tactics/positionfactory.cpp
    src/match/match.cpp
    src/match/match_state.cpp
    src/match/play.cpp
    src/match/match_enterpitch.cpp
    src/match/match_lineup.cpp
    src/match/kickoff.cpp
    src/match/goalkick.cpp
    src/match/throwin.cpp
    src/match/corner.cpp
    src/match/freekick.cpp
    src/player/playerfactory.cpp
    src/player/player.cpp
    src/player/states/player_state.cpp
    src/player/states/standing.cpp
    src/player/states/running.cpp
    src/player/states/sliding.cpp
    src/player/states/jumping.cpp
    src/ball/ball.cpp
    src/ball/ballfactory.cpp
    src/pitch/pitch.cpp
    src/pitch/pitchwidget.cpp
    src/player/locomotion/locomotionmanager.cpp
    src/player/locomotion/locomotion.cpp
    src/player/locomotion/stand.cpp
    src/player/locomotion/seek.cpp
    src/player/locomotion/head.cpp
    src/player/locomotion/pursue.cpp
    src/player/locomotion/locomotion_slide.cpp
    src/player/ai/brain.cpp
    src/player/ai/brainstate.cpp
    src/player/ai/brain_idle.cpp
    src/player/ai/retrieve.cpp
    src/player/ai/jump.cpp
    src/player/ai/goto.cpp
    src/player/ai/attack/dribble.cpp
    src/player/ai/attack/pass.cpp
    src/player/ai/attack/receivepass.cpp
    src/player/ai/attack/shoot.cpp
    src/player/ai/defend/brain_slide.cpp
    src/player/ai/defend/cover.cpp
    src/debug/diagnostics.cpp
)

# --------------------------------------------------
# link libs
# --------------------------------------------------
find_package(OpenGL)
target_link_libraries (senseless_soccer ${OPENGL_gl_LIBRARY})
target_link_libraries (senseless_soccer gamelib2)
target_link_libraries (senseless_soccer sfml-graphics-d)
target_link_libraries (senseless_soccer sfml-window-d)
target_link_libraries (senseless_soccer sfml-system-d)
