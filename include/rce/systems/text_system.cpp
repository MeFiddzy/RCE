#include <algorithm>
#include "text_system.h"

using namespace rce;

void TextSystem::onSceneTick(std::weak_ptr<IScene> scene) {
    std::sort(m_textObjects.begin(), m_textObjects.end(), [&](const std::shared_ptr<TextObject> &a, std::shared_ptr<TextObject> &b){
        return a->getZOrder() < b->getZOrder();
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

void TextSystem::addText(const TextObject &object) {
    m_textObjects.push_back(std::make_shared<TextObject>(object));
}
