#pragma once

#include "scene.h"

namespace rce {
    class ExampleScene : public IScene {
    public:
        void gameLoop() override;

        void loadScene() override;
    private:

    };
}