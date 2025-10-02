#pragma once
#include "hitbox_component.h"
#include "../object.h"

using mefiddzy::Hitbox;

mefiddzy::Hitbox::OnHitElem::OnHitElem(std::vector<std::function<void(const Object &)>> &onHit,
                                       Hitbox &hitbox) : m_onHit(onHit), m_hitbox(hitbox) {}

void mefiddzy::Hitbox::onTick(mefiddzy::Object &parent) {
    static auto getRect = [](const Object &obj) {
        const float height = obj.getTexture().height;
        const float width = obj.getTexture().width;

        Rectangle rect;
        rect.x = obj.getCoords().x;
        rect.y = obj.getCoords().y;

        rect.height = height;
        rect.width = width;

        return rect;
    };

    const float height = parent.getTexture().height;
    const float width = parent.getTexture().width;

    Rectangle hitbox = getRect(parent);

    for (const auto objLoop : mefiddzy::Object::getAllObjects()) {
        if (objLoop == &parent)
            continue;

        Rectangle curRect = getRect(*objLoop);

        if (CheckCollisionRecs(hitbox, curRect)) {
            for (const auto &listener : m_onHit) {
                listener(*objLoop);
            }
        }
    }
}



