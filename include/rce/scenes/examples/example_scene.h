#pragma once

#include "rce/scenes/scene.h"

namespace rce::examples {
    class ExampleScene : public IScene {
    public:
        void onTick() override;

        void onLoad() override;
    private:

    };
}