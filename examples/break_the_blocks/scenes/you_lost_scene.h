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

            auto You = m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                "You",
                200,
                10,
                {
                    220, 100
                },
                WHITE
            }));

            auto Lost = m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                "Lost",
                200,
                10,
                {
                    200, 300
                },
                WHITE
            }));
        }
    };
}
