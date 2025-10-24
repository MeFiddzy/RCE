#include <iostream>
#include <raylib.h>
#include <memory>

#include "rce/scenes/scene.h"
#include "rce/scenes/examples/example_scene.h"

#include "rce/object_components//all.h"
#include "rce/object.h"

int main() {
    // create window
    InitWindow(640, 480, "TestNeim");
    SetTargetFPS(180);

    using namespace rce;

    // load scene
    IScene::loadScene<examples::ExampleScene>();

    /// game loop
    while (!WindowShouldClose()) {
        if (IScene::getLoaded().expired())
            continue;

        std::shared_ptr<IScene> scene = IScene::getLoaded().lock();

        BeginDrawing();
        ClearBackground(scene->getBackgroundColor());

        // tick scenes
        scene->onTick();

        for (const auto &weakComponent : scene->getSystems()) {
            if (!weakComponent.expired()) {
                auto component = weakComponent.lock();
                if (component->isEnabled())
                    component->onSceneTick(scene);
            }
        }

        // update object position and object_components
        Object::update();
        EndDrawing();

    }

    CloseWindow();

    // unload scene;
    if (IScene::getLoaded().expired())
        return 0;

    IScene::getLoaded().lock()->onUnLoad();
}