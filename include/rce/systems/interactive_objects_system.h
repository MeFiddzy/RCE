#pragma once
#include "system.h"

namespace rce {
    struct InteractiveObjectsSystem : ISystem {
        InteractiveObjectsSystem() = default;

        void onSceneTick(std::weak_ptr<IScene> scene) override;
    };
}
