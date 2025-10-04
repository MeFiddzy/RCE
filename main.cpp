#include <iostream>
#include <raylib.h>
#include <memory>

#include "scenes/scene.h"
#include "components/all.h"
#include "scenes/example_scene"
#include "object.h"

int main() {
    InitWindow(640, 480, "TestNeim");
    SetTargetFPS(60);

    using namespace mefiddzy;
    using namespace mefiddzy::scenes;

    IScene::loadScene<ExampleScene>();

    while (!WindowShouldClose()) {
        if (IScene::getLoaded().expired())
            continue;

        std::shared_ptr<IScene> scene = IScene::getLoaded().lock();\

        BeginDrawing();
        ClearBackground(scene->getBackgroundColor());

        scene->gameLoop();

        Object::update();
        EndDrawing();

    }

    CloseWindow();
}
