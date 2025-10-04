cmake_minimum_required(VERSION 3.27)
project(raylib_object_engine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

option(DEBUG "Debug mode?" ON)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

add_executable(raylib_object_engine
        main.cpp
        object.cpp
        object.h
        components/component.h
        components/hitbox_component.cpp
        components/hitbox_component.h
        components/all.h
        scenes/scene.h
        scenes/ex_scene.cpp
        scenes/example_scene
        scenes/scene.cpp
        components/children_component.h
        components/children_component.cpp
)

target_link_libraries(raylib_object_engine PRIVATE raylib)

if (DEBUG)
    set_target_properties(raylib_object_engine PROPERTIES WIN32_EXECUTABLE FALSE)
else()
    set_target_properties(raylib_object_engine PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
