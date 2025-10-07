#pragma once

#include "scene.h"

namespace rce {
    class ExampleScene : public IScene {
    public:
        void onTick() override;

        void onLoad() override;
    private:

    };
}