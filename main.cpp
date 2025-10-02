#include <iostream>
#include <raylib.h>
#include <memory>

#include "scenes/scene.h"
#include "scenes/ex_scene.h"
#include "object.h"

int main() {
    InitWindow(640, 480, "TestNeim");
    SetTargetFPS(60);

    using namespace mefiddzy;

    scenes::IScene::loadScene<scenes::ExampleScene>();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!(scenes::IScene::getLoaded().expired()))
            scenes::IScene::getLoaded().lock()->gameLoop();

        Object::update();
        EndDrawing();

    }

    CloseWindow();
}
