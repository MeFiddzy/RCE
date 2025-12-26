cmake_minimum_required(VERSION 3.27)
project(rce LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

add_executable(rce
        include/rce/objects/sprite_object.cpp
        include/rce/objects/sprite_object.h
        include/rce/object_components/object_component.h
        include/rce/object_components/hitbox_component.cpp
        include/rce/object_components/hitbox_component.h
        include/rce/object_components/all.h
        include/rce/scenes/scene.h
        include/rce/scenes/test/test_scene.cpp
        include/rce/scenes/test/test_scene.h
        include/rce/scenes/scene.cpp
        include/rce/object_components/children_component.h
        include/rce/object_components/children_component.cpp
        include/rce/object_components/find_object_component.h
        include/rce/object_components/find_object_component.cpp
        include/rce/systems/system.h
        include/rce/object_components/object_component.cpp
        include/rce/systems/system.cpp
        include/rce/objects/text_object.cpp
        include/rce/objects/text_object.h
        include/rce/objects/abstract_object.h
        include/rce/objects/abstract_object.cpp
        include/rce/util/Property.h
        include/rce/util/tags.h
        examples/break_the_blocks/break_the_blocks.cpp
        examples/break_the_blocks/scenes/break_the_blocks_scene.cpp
        examples/break_the_blocks/scenes/break_the_blocks_scene.h
        include/rce/objects/shape/rectangle_object.cpp
        include/rce/objects/shape/rectangle_object.h
        include/rce/objects/shape/circle_object.cpp
        include/rce/objects/shape/circle_object.h
        examples/break_the_blocks/components/mini_physics_component.cpp
        examples/break_the_blocks/components/mini_physics_component.h
        examples/break_the_blocks/scenes/you_lost_scene.h
        examples/break_the_blocks/lib/util.h
        examples/break_the_blocks/systems/gen_cubes_system.cpp
        examples/break_the_blocks/systems/gen_cubes_system.h
        include/rce/objects/interactive/interactive_object.h
        include/rce/objects/interactive/buttons/rectangle_button.h
        examples/break_the_blocks/scenes/start_menu_scene.h
        include/rce/systems/interactive_objects_system.h
        include/rce/systems/interactive_object_system.cpp
        examples/break_the_blocks/scenes/start_menu_scene.cpp
        include/rce/objects/interactive/switches/abstract_switch.h
        include/rce/objects/interactive/buttons/abstract_button.h
        include/rce/objects/interactive/switches/rectangle_switch.h
        examples/platformer/platformer.cpp
        examples/platformer/scene/play_scene.h
        examples/platformer/scene/play_scene.cpp
        examples/platformer/components/physics_component.h
        examples/platformer/components/physics_component.cpp
        examples/platformer/objects/orb_object.cpp
        examples/platformer/objects/orb_object.h
        examples/pong/pong.cpp
        examples/pong/scenes/pong_scene.cpp
        examples/pong/components/mini_physics_component_p.cpp
        examples/pong/scenes/win_scene.h
        examples/pong/scenes/play_menu_scene.h
        examples/pong/util/settings_data.h
        examples/pong/scenes/settings_scene.h
        include/rce/objects/interactive/text_boxs/text_box.h
        include/rce/objects/interactive/text_boxs/text_box.cpp
        include/rce/objects/interactive/text_boxs/rectangle_textbox.h
)

target_include_directories(rce PRIVATE include)

target_link_libraries(rce PRIVATE raylib)