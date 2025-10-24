#pragma once

#include <vector>
#include "system.h"
#include "rce/objects/text_object.h"

namespace rce {
    class TextSystem : public ISystem {
    public:
        void onSceneTick(std::weak_ptr<IScene> scene) override;

    private:
        std::vector<std::shared_ptr<TextObject>> m_textObjects;
    };
}