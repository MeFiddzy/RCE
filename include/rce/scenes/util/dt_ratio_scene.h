#pragma once

#include "rce/scenes/scene.h"

namespace rce {
    /**
     * @brief This scene helps you find an delta time ratio (for more info, check include/rce/scenes/scene.h, line 8 - 12).
     * The longer you keep and app with this scene on, the more accurate is the result.
     * This is intended to be run at 60 FPS.
     */
    class DeltaTimeRatioScene : public IScene {
    public:
        void onTick() override;

        void onUnLoad() override;
    private:
        float m_sum = 0;
    };
}