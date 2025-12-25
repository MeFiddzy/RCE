#include <raylib.h>
#include <memory>

#include "rce/objects/abstract_object.h"
#include "rce/scenes/scene.h"
#include "scene/play_scene.h"

int main() {
    // create window
    InitWindow(1300, 1200, "Platformer");
    SetTargetFPS(60);

    using namespace rce;

    // load scene
    IScene::loadScene<examples::PlayScene>();

    /// game loop
    while (!WindowShouldClose()) {
        if (IScene::getLoaded().expired())
            continue;

        std::shared_ptr<IScene> scene = IScene::getLoaded().lock();

        BeginDrawing();
        ClearBackground(scene->getBackgroundColor());

        // update object position and object_components
        AbstractObject::update();

        for (const auto &weakSystem : scene->getSystems()) {
                if (!weakSystem.expired()) {
                auto system = weakSystem.lock();
                if (system->isEnabled())
                    system->onSceneTick(scene);
            }
        }

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
