#pragma once

#include "scene.h"

namespace rce {
    class ExampleScene : public IScene {
    public:
        void ofTick() override;

        void onLoadScene() override;
    private:

    };
}