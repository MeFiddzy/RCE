#pragma once
#include "../components/mini_physics_component.h"
#include "../../../include/rce/objects/shape/rectangle_object.h"
#include "rce/objects/text_object.h"
#include "rce/scenes/scene.h"
#include "rce/util/tags.h"

namespace rce {
    class CircleObject;
}

namespace rce::examples {
    class BreakTheBlocksScene : public IScene {
    public:
        explicit BreakTheBlocksScene(bool slippery) : m_slippery(slippery) {}

        void onTick() override;
        void onLoad() override;

        static const Tag& getCubeTag() {
            return s_cubeTag;
        }

        static const Tag& getPaddleTag() {
            return s_paddleTag;
        }

    private:
        std::shared_ptr<RectangleObject> m_paddle;
        std::shared_ptr<CircleObject> m_ball;
        std::shared_ptr<MiniPhysicsComponent> m_physicsBall;
        std::shared_ptr<MiniPhysicsComponent> m_physicsPaddle;

        bool m_slippery;

        // std::shared_ptr<TextObject> m_comboText;
        // std::shared_ptr<TextObject> m_maxComboText;

        const static Tag s_cubeTag;
        const static Tag s_paddleTag;
    };
}
