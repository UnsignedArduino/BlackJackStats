cmake_minimum_required(VERSION 3.25)
project("BlackJackStats")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp")

add_executable(main ${sources})
