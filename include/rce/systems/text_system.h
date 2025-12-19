#pragma once

#include <vector>
#include "system.h"
#include "rce/objects/text_object.h"

namespace rce {
    class TextSystem : public ISystem {
    public:
        void onSceneTick(std::weak_ptr<IScene> scene) override;

        void addText(const TextObject &object);

    private:
        std::vector<std::shared_ptr<TextObject>> m_textObjects;
    };
}