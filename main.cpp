#include <iostream>
#include <raylib.h>
#include <memory>

#include "rce/scenes/scene.h"
#include "rce/scenes/examples/example_scene.h"
#include "rce/scenes/util/dt_ratio_scene.h"

#include "rce/components/all.h"
#include "rce/object.h"

int main() {
    // create window
    InitWindow(640, 480, "TestNeim");
    SetTargetFPS(60);

    using namespace rce;
    using namespace rce::examples;

    // load scene
    IScene::loadScene<ExampleScene>();

    /// game loop
    while (!WindowShouldClose()) {
        if (IScene::getLoaded().expired())
            continue;

        std::shared_ptr<IScene> scene = IScene::getLoaded().lock();

        BeginDrawing();
        ClearBackground(scene->getBackgroundColor());

        // tick scenes
        scene->onTick();

        // update object position and components
        Object::update();
        EndDrawing();

    }

    CloseWindow();

    // unload scene;
    if (IScene::getLoaded().expired())
        return 0;

    IScene::getLoaded().lock()->onUnLoad();
}
