#pragma once
#include "rce/objects/text_object.h"
#include "rce/scenes/scene.h"

namespace rce::examples {
    class YouLostScene : public IScene {
    public:
        void onTick() override {
            if (IsKeyDown(KEY_R)) {
                loadScene<BreakTheBlocksScene>();
            }
        }

        void onLoad() override {
            m_backgroundColor = Color(41, 21, 99);

            auto you = m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                "You",
                400,
                10,
                {
                    260, 200
                },
                WHITE
            }));

            auto lost = m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                "Lost",
                400,
                10,
                {
                    260, 530
                },
                WHITE
            }));

            auto restartInfo = m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                "Press [R] to Restart!",
                50,
                10,
                {
                    360, 1000
                },
                WHITE
            }));
        }
    };
}
