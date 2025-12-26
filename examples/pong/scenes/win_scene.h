#pragma once
#include <format>

#include "rce/objects/text_object.h"
#include "rce/scenes/scene.h"

namespace rce::examples {
    class WinScene : public IScene {
    public:
        explicit WinScene(const bool won, const SettingsData& settingsData) {
            m_won = won;
            m_settingsData = settingsData;
        }

        void onTick() override {
            if (IsKeyPressed(KEY_R)) {
                loadScene<PongScene>(m_settingsData);
            }
        }

        void onLoad() override {
            m_backgroundColor = Color(41, 21, 99);

            m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                std::format("Player {}\nhas won!", m_won == 1 ? "1" : "2"),
                200,
                10,
                {260, 400},
                WHITE
            }));

            m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                "Press \'R\' to restart!",
                50,
                10,
                {350, 900},
                WHITE
            }));

        }

    private:
        char m_won;

        SettingsData m_settingsData;
    };
}
