#include <algorithm>
#include "text_system.h"

using namespace rce;

void TextSystem::onSceneTick(std::weak_ptr<IScene> scene) {
    std::sort(m_textObjects.begin(), m_textObjects.end(), [&](const std::weak_ptr<TextObject> &a, std::weak_ptr<TextObject> &b){
        if (a.expired() || b.expired())
            return false;

        return a.lock()->getZOrder() < b.lock()->getZOrder();
    });

    for (const auto &textObject : m_textObjects) {
        DrawTextEx(
                textObject->getFont(),
                textObject->getText().data(),
                textObject->getPosition(),
                textObject->getFontSize(),
                textObject->getSpacing(),
                textObject->getTint()
        );
    }
}
