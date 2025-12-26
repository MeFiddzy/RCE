#pragma once
#include "settings_scene.h"
#include "rce/objects/interactive/buttons/rectangle_button.h"
#include "rce/scenes/scene.h"
#include "rce/systems/interactive_objects_system.h"

namespace rce::examples {
    class PlayMenuScene : public IScene {
    public:
        explicit PlayMenuScene(const SettingsData& settingsData) { m_settingsData = settingsData; }

        void onLoad() override {
            m_backgroundColor = Color(41, 21, 99);

            addSystem(std::make_shared<InteractiveObjectsSystem>());

            addObject(std::make_shared<TextObject>(TextObject{
                "Pong",
                300,
                10,
                {330, 350},
                WHITE,
            }));

            m_objects.emplace_back(std::make_shared<RectangleButton>(RectangleButton{
                {350, 900},
                {0, 0},
                0.0f,
                WHITE,
                600,
                100,
                [&](const Vector2& clickPos, InteractiveObject* self) {
                    loadScene<PongScene>(m_settingsData);
                }
            }));

            m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                "Start Game",
                50,
                10,
                {475, 925},
                BLACK
            }));

            m_objects.emplace_back(std::make_shared<RectangleButton>(RectangleButton{
                {450, 1050},
                {0, 0},
                0.0f,
                WHITE,
                400,
                100,
                [&](const Vector2& clickPos, InteractiveObject* self) {
                    loadScene<SettingsScene>(m_settingsData);
                }
            }));

            m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                "Settings",
                50,
                10,
                {525, 1075},
                BLACK
            }));
        }
    private:
        SettingsData m_settingsData;
    };
}
