#pragma once
#include "../components/mini_physics_component_p.h"
#include "../../../include/rce/objects/shape/rectangle_object.h"
#include "rce/objects/text_object.h"
#include "rce/scenes/scene.h"
#include "rce/util/tags.h"
#include "../util/settings_data.h"

namespace rce {
    class CircleObject;
}

namespace rce::examples {
    class PongScene : public IScene {
    public:
        explicit PongScene(const SettingsData& settingsData) {
            m_settingsData = settingsData;
        }

        void onTick() override;
        void onLoad() override;

        static const Tag& getCubeTag() {
            return s_cubeTag;
        }

        static const Tag& getPaddleTag() {
            return s_paddleTag;
        }

    private:
        void onScoreAdd() const;

        std::shared_ptr<TextObject> m_scoreTextP1;
        std::shared_ptr<TextObject> m_scoreTextP2;

        std::shared_ptr<RectangleObject> m_paddleP1;
        std::shared_ptr<RectangleObject> m_paddleP2;

        std::shared_ptr<CircleObject> m_ball;
        std::shared_ptr<MiniPhysicsComponentP> m_physicsBall;

        std::shared_ptr<MiniPhysicsComponentP> m_physicsPaddleP1;
        std::shared_ptr<MiniPhysicsComponentP> m_physicsPaddleP2;

        uint8_t m_scoreP1 = 0;
        uint8_t m_scoreP2 = 0;

        SettingsData m_settingsData;

        const static Tag s_cubeTag;
        const static Tag s_paddleTag;
    };
}
