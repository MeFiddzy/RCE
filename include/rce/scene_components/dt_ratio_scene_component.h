#pragma once

#include "rce/scene_components/scene_component.h"

namespace rce {
    /**
     * @brief This scene helps you find an delta time ratio (for more info, check include/rce/scenes/scene.h, line 8 - 12).
     * The longer you keep and app with this scene on, the more accurate is the result.
     * This is intended to be run at 60 FPS.
     */
    class DeltaTimeRatioSceneComponent : public ISceneComponent {
    public:
        void onSceneUnLoad(std::weak_ptr<IScene> scene) override;

        void onSceneTick(std::weak_ptr<IScene> scene) override;
    private:
        float m_sum = 0;
    };
}