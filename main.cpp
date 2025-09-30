#include <iostream>
#include "object.h"
#include "raylib.h"


int main() {
    InitWindow(640, 480, "TestNeim");
    SetTargetFPS(60);

    std::cout << "[MESSAGE] Started";

    using mefiddzy::Object;

    Object soul(
            Vector2{0, 0},
            LoadTexture("../resources/player.png")
    );

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyDown(KEY_F4)) {
            ToggleBorderlessWindowed();
        }

        Object::update();
        EndDrawing();
    }

    CloseWindow();
}
