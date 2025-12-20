#include <raylib.h>
#include <memory>
#include <random>

#include "rce/scenes/scene.h"
#include "scenes/break_the_blocks_scene.h"
#include "rce/objects/sprite_object.h"

namespace rce {
    class IScene;
}

int main() {


    // create window
    InitWindow(800, 600, "Break The Blocks");
    SetTargetFPS(60);

    using namespace rce;

    // load scene
    IScene::loadScene<examples::BreakTheBlocksScene>();

    /// game loop
    while (!WindowShouldClose()) {
        if (IScene::getLoaded().expired())
            continue;

        std::shared_ptr<IScene> scene = IScene::getLoaded().lock();

        BeginDrawing();
        ClearBackground(scene->getBackgroundColor());

        for (const auto &weakComponent : scene->getSystems()) {
            if (!weakComponent.expired()) {
                auto system = weakComponent.lock();
                if (system->isEnabled())
                    system->onSceneTick(scene);
            }
        }

        // update object position and object_components
        SpriteObject::update();

        // tick scenes
        scene->onTick();
        EndDrawing();

    }

    CloseWindow();

    // unload scene;
    if (IScene::getLoaded().expired())
        return 0;

    IScene::getLoaded().lock()->onUnLoad();
}
