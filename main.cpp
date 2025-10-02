#include <iostream>
#include "object.h"
#include <hitbox_component.h>
#include <raylib.h>
#include <memory>

int main() {
    InitWindow(640, 480, "TestNeim");
    SetTargetFPS(60);

    using namespace mefiddzy;

    Object player(
            Vector2{0, 0},
            LoadTexture("../resources/player.png")
    );

    player.addComponent(std::make_unique<Hitbox>(
            Hitbox(player).onHit().addListener([](const Object &self){
                std::cout << "collision\n";
            }).build()
    ));

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_F4)) {
            ToggleBorderlessWindowed();
        }

        Object::update();
        EndDrawing();
    }

    CloseWindow();
}
