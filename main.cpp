#include <iostream>
#include <raylib.h>
#include <memory>

#include "rce/scenes/scene.h"
#include "rce/components/all.h"
#include "rce/scenes/example_scene.h"
#include "rce/object.h"

int main() {
    InitWindow(640, 480, "TestNeim");
    SetTargetFPS(60);

    using namespace rce;

    IScene::loadScene<ExampleScene>();

    while (!WindowShouldClose()) {
        if (IScene::getLoaded().expired())
            continue;

        std::shared_ptr<IScene> scene = IScene::getLoaded().lock();

        BeginDrawing();
        ClearBackground(scene->getBackgroundColor());

        scene->onTick();

        Object::update();
        EndDrawing();

    }

    CloseWindow();
}
