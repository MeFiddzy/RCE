#pragma once
#include "../components/physics_component.h"
#include "rce/objects/shape/rectangle_object.h"
#include "rce/scenes/scene.h"

namespace rce::examples {
    class PlayScene : public IScene {
    public:
        void onTick() override;
        void onLoad() override;

    private:
        std::shared_ptr<RectangleObject> m_cube;
        std::shared_ptr<RectangleObject> m_ground;

        std::shared_ptr<HitboxComponent> m_actualCubeHitbox;

        std::shared_ptr<PhysicsComponent> m_cubePhysics;
        std::shared_ptr<PhysicsComponent> m_groundPhysics;
    };
}
