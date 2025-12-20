#include <raylib.h>
#include <memory>

#include "rce/scenes/scene.h"
#include "rce/scenes/test/test_scene.h"
#include "scenes/break_the_blocks_scene.h"
#include "rce/object_components/all.h"
#include "rce/objects/sprite_object.h"

namespace rce {
    class IScene;
}

int main() {
    // create window
    InitWindow(800, 600, "Break The Blocks");
    SetTargetFPS(180);

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

        // tick scenes
        scene->onTick();

        for (const auto &weakComponent : scene->getSystems()) {
            if (!weakComponent.expired()) {
                auto system = weakComponent.lock();
                if (system->isEnabled())
                    system->onSceneTick(scene);
            }
        }

        // update object position and object_components
        SpriteObject::update();
        EndDrawing();

    }

    CloseWindow();

    // unload scene;
    if (IScene::getLoaded().expired())
        return 0;

    IScene::getLoaded().lock()->onUnLoad();
}
