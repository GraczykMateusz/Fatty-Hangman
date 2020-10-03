cmake_minimum_required(VERSION 3.10)

project(FattyHangman)

set(ScriptPath src/)

add_executable(FattyHangman ${ScriptPath}main.cpp ${ScriptPath}Game.cpp)

add_library(Game ${ScriptPath}Game.h ${ScriptPath}Game.cpp)
add_library(Hangman ${ScriptPath}Hangman.h ${ScriptPath}Hangman.cpp)

target_link_libraries(FattyHangman PUBLIC Game)
target_link_libraries(FattyHangman PUBLIC Hangman)

