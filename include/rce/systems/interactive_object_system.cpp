#include "interactive_objects_system.h"
#include "rce/objects/interactive/interactive_object.h"

using namespace rce;

void InteractiveObjectsSystem::onSceneTick(const std::weak_ptr<IScene> scene) {
    if (scene.expired())
        return;

    const auto sceneObjects = ISystem::getObjectsFromScene(scene.lock().get());
    const Vector2 mouse = GetMousePosition();

    for (const auto& object : *sceneObjects) {
        const auto interactive = std::dynamic_pointer_cast<InteractiveObject>(object);
        if (!interactive)
            continue;

        const Rectangle trigger = interactive->getTriggerShape();

        if (CheckCollisionPointRec(mouse, trigger)) {
            interactive->onHover(mouse, interactive.get());

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                interactive->onClick(mouse, interactive.get());

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                interactive->onButtonDown(mouse, interactive.get());

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                interactive->onRelease(mouse, interactive.get() );
        }
    }
}
