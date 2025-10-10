cmake_minimum_required(VERSION 3.27)
project(rce LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(DEBUG "Debug mode?" ON)


include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

add_executable(rce
        main.cpp
        include/rce/object.cpp
        include/rce/object.h
        include/rce/components/component.h
        include/rce/components/hitbox_component.cpp
        include/rce/components/hitbox_component.h
        include/rce/components/all.h
        include/rce/scenes/scene.h
        include/rce/scenes/ex_scene.cpp
        include/rce/scenes/example_scene.h
        include/rce/scenes/scene.cpp
        include/rce/components/children_component.h
        include/rce/components/children_component.cpp
        include/rce/components/find_object_component.h
        include/rce/components/find_object_component.cpp
)

target_include_directories(rce PRIVATE include)

target_link_libraries(rce PRIVATE raylib)

if (DEBUG)
    set_target_properties(rce PROPERTIES WIN32_EXECUTABLE FALSE)
else()
    set_target_properties(rce PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
