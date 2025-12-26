#pragma once
#include <format>

#include "rce/objects/interactive/buttons/rectangle_button.h"
#include "rce/objects/interactive/switches/rectangle_switch.h"
#include "rce/objects/interactive/text_boxs/rectangle_textbox.h"
#include "rce/scenes/scene.h"
#include "rce/systems/interactive_objects_system.h"
#include "util/settings_data.h"

namespace rce::examples {
    class PlayMenuScene;

    class SettingsScene : public IScene {
    public:
        explicit SettingsScene(const SettingsData& settingsData) { m_settingsData = settingsData; }

        void onLoad() override {
            m_backgroundColor = Color(41, 21, 99);

            addSystem(std::make_shared<InteractiveObjectsSystem>());

            m_p1InvertedSwitch = addObject(std::make_shared<RectangleSwitch>(RectangleSwitch{
                {100, 50},
                {},
                0.f,
                50.f,
                50.f,
                GREEN,
                RED
            }));
            m_p1InvertedSwitch->setValue(m_settingsData.p1InvertedControls);
            addObject(std::make_shared<TextObject>(TextObject{
                "P1 Inverted Controls",
                40,
                10,
                {200, 60},
                WHITE
            }));

            m_p2InvertedSwitch = addObject(std::make_shared<RectangleSwitch>(RectangleSwitch{
                {100, 150},
                {},
                0.f,
                50.f,
                50.f,
                GREEN,
                RED
            }));
            m_p2InvertedSwitch->setValue(m_settingsData.p1InvertedControls);
            addObject(std::make_shared<TextObject>(TextObject{
                "P2 Inverted Controls",
                40,
                10,
                {200, 160},
                WHITE
            }));

            m_p1Size = addObject(std::make_shared<RectangleTextBox>(RectangleTextBox{
                {100, 250},
                {},
                0.f,
                WHITE,
                600.f,
                50.f,
                15
            }));
            m_p1Size->setValue(std::format("{} {}", m_settingsData.p1Size.x, m_settingsData.p1Size.y));
            addObject(std::make_shared<TextObject>(TextObject{
                "P1 Size",
                40,
                10,
                {750, 260},
                WHITE
            }));

            m_p2Size = addObject(std::make_shared<RectangleTextBox>(RectangleTextBox{
                {100, 350},
                {},
                0.f,
                WHITE,
                600.f,
                50.f,
                15
            }));
            m_p2Size->setValue(std::format("{} {}", m_settingsData.p2Size.x, m_settingsData.p2Size.y));
            addObject(std::make_shared<TextObject>(TextObject{
                "P2 Size",
                40,
                10,
                {750, 360},
                WHITE
            }));

            m_p1Movement = addObject(std::make_shared<RectangleTextBox>(RectangleTextBox{
                {100, 450},
                {},
                0.f,
                WHITE,
                600.f,
                50.f,
                15
            }));
            m_p1Movement->setValue(std::format("{} {}", m_settingsData.p1Movement.x, m_settingsData.p1Movement.y));
            addObject(std::make_shared<TextObject>(TextObject{
                "P1 Movement",
                40,
                10,
                {750, 460},
                WHITE
            }));

            m_p2Movement = addObject(std::make_shared<RectangleTextBox>(RectangleTextBox{
                {100, 550},
                {},
                0.f,
                WHITE,
                600.f,
                50.f,
                15
            }));
            m_p2Movement->setValue(std::format("{} {}", m_settingsData.p2Movement.x, m_settingsData.p2Movement.y));
            addObject(std::make_shared<TextObject>(TextObject{
                "P2 Movement",
                40,
                10,
                {750, 560},
                WHITE
            }));

            m_winScore = addObject(std::make_shared<RectangleTextBox>(RectangleTextBox{
                {100, 650},
                {},
                0.f,
                WHITE,
                600.f,
                50.f,
                15
            }));
            m_winScore->setValue(std::to_string(m_settingsData.winScore));
            addObject(std::make_shared<TextObject>(TextObject{
                "Win Score",
                40,
                10,
                {750, 660},
                WHITE
            }));

            addObject(std::make_shared<RectangleButton>(RectangleButton{
                {900, 1000},
                {},
                0.f,
                WHITE,
                300,
                80,
                [&](const Vector2& pos, InteractiveObject* self) {
                    IScene::loadScene<PlayMenuScene>(m_settingsData);
                }
            }));
            addObject(std::make_shared<TextObject>(TextObject{
                "Back",
                70,
                20,
                {925, 1010},
                BLACK
            }));
        }
    private:
        using Switch = std::shared_ptr<RectangleSwitch>;
        using TextBox = std::shared_ptr<RectangleTextBox>;

        SettingsData m_settingsData;

        Switch m_p1InvertedSwitch;
        Switch m_p2InvertedSwitch;

        TextBox m_p1Size;
        TextBox m_p2Size;

        TextBox m_p1Movement;
        TextBox m_p2Movement;

        TextBox m_winScore;
    };
}
