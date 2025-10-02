#pragma once

#include "scene.h"

namespace mefiddzy::scenes {
    class ExampleScene : public IScene {
    public:
        void gameLoop() override;

        std::vector<std::unique_ptr<Object>> getObjectsForLoad() override;
    };
}