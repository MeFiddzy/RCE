#pragma once
#include "../components/mini_physics_component.h"
#include "rce/objects/text_object.h"
#include "../../../include/rce/objects/interactive/buttons/rectangle_button.h"
#include "rce/objects/interactive/switches/rectangle_switch.h"
#include "rce/scenes/scene.h"

namespace rce::examples {
    class StartMenuScene : public IScene {
    public:
        void onLoad() override;

    private:
        std::shared_ptr<TextObject> m_breakoidText;
        std::shared_ptr<RectangleButton> m_startGameButton;
        std::shared_ptr<RectangleSwitch> m_slipperyModeSwitch;

        constexpr static float s_velocityToAddY = 20;
    };
}
