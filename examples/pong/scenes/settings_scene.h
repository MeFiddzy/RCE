#pragma once
#include "rce/objects/interactive/buttons/rectangle_button.h"
#include "rce/objects/interactive/switches/rectangle_switch.h"
#include "rce/scenes/scene.h"
#include "rce/systems/interactive_objects_system.h"
#include "util/settings_data.h"

namespace rce::examples {
    class SettingsScene : public IScene {
    public:
        explicit SettingsScene(const SettingsData& settingsData) { m_settingsData = settingsData; }

        void onLoad() override {
            m_backgroundColor = Color(41, 21, 99);

            addSystem(std::make_shared<InteractiveObjectsSystem>());

            m_p1InvertedSwitch = std::dynamic_pointer_cast<RectangleSwitch>(
                m_objects.emplace_back(std::make_shared<RectangleSwitch>(RectangleSwitch{
                    {100, 50},
                    {},
                    0.f,
                    50.f,
                    50.f,
                    GREEN,
                    RED
                })
            ));
            m_p1InvertedSwitch->setValue(m_settingsData.p1InvertedControls);
        }
    private:
        SettingsData m_settingsData;
        using SwitchRect = std::shared_ptr<RectangleSwitch>;

        SwitchRect m_p1InvertedSwitch;
        SwitchRect m_p2InvertedSwitch;
    };
}
