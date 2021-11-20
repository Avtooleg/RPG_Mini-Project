cmake_minimum_required(VERSION 3.20)
project(RPG_miniproject)

set(CMAKE_CXX_STANDARD 14)

add_executable(RPG_miniproject main.cpp Creature.cpp Player.cpp Map.cpp Frontend.cpp Player.cpp Utils.cpp)
