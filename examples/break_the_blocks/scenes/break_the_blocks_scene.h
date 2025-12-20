#pragma once
#include "rce/scenes/scene.h"

namespace rce::examples {
    class BreakTheBlocksScene : public IScene {
        void onTick() override;
        void onLoad() override;
    };
}
