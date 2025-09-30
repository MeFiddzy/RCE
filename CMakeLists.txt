cmake_minimum_required(VERSION 3.27)
project(raylib_undertale_engine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

option(DEBUG "Debug mode?" ON)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

add_executable(raylib_undertale_engine
        main.cpp
        object.cpp
        object.h
)

target_link_libraries(raylib_undertale_engine PRIVATE raylib)

if (DEBUG)
    set_target_properties(raylib_undertale_engine PROPERTIES WIN32_EXECUTABLE FALSE)
else()
    set_target_properties(raylib_undertale_engine PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
