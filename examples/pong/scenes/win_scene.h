#pragma once
#include <format>

#include "rce/objects/text_object.h"
#include "rce/scenes/scene.h"

namespace rce::examples {
    class WinScene : public IScene {
    public:
        explicit WinScene(const bool won) { m_won = won; }

        void onLoad() override {
            m_backgroundColor = Color(41, 21, 99);

            m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
                std::format("Player {}\nhas won!", m_won == 1 ? "1" : "2"),
                200,
                10,
                {260, 400},
                WHITE
            }));
        }

    private:
        char m_won;
    };
}
