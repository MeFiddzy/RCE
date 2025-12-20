#pragma once
#include "../components/mini_physics_component.h"
#include "rce/objects/rectangle_object.h"
#include "rce/scenes/scene.h"
#include "rce/util/tags.h"

namespace rce {
    class CircleObject;
}

namespace rce::examples {
    class BreakTheBlocksScene : public IScene {
    public:
        void onTick() override;
        void onLoad() override;

    static const Tag& getBounceableTag() {
        return s_bounceableTag;
    }

    private:
        std::shared_ptr<RectangleObject> m_paddle;
        std::shared_ptr<CircleObject> m_ball;
        std::shared_ptr<MiniPhysicsComponent> m_physicsBall;

        const static Tag s_bounceableTag;
    };
}
