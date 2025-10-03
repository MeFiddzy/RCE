#include "hitbox_component.h"
#include "../object.h"
#include "../scenes/scene.h"

#define SHOW_HITBOXES true

using mefiddzy::Hitbox;

mefiddzy::Hitbox::OnHitElem::OnHitElem(std::vector<std::function<void(const Object &)>> &onHit,
                                       Hitbox &hitbox) : m_onHit(onHit), m_hitbox(hitbox) {}

void mefiddzy::Hitbox::onTick(mefiddzy::Object &parent) {
    Rectangle hitbox = {
            parent.getCoords().x + m_collisionBoxOffset.x,
            parent.getCoords().y + m_collisionBoxOffset.y,
            m_collisionBoxSize.x,
            m_collisionBoxSize.y
    };
#if SHOW_HITBOXES
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, RED);
#endif

    if (mefiddzy::scenes::IScene::getLoaded().expired())
        return;

    std::vector<Object*> objectsInScene = mefiddzy::scenes::IScene::getLoaded().lock()->getLoadedObjects();

    for (Object *loopObj : objectsInScene) {
        if (loopObj == &parent || !(loopObj->hasComponent<Hitbox>()))
            continue;

        const auto &hitboxObj = loopObj->getComponent<Hitbox>();
        const auto &hitboxBoxSize = hitboxObj.m_collisionBoxSize;
        const auto &hitboxBoxOffset = hitboxObj.m_collisionBoxOffset;

        Rectangle curRect = {
                loopObj->getCoords().x + hitboxBoxOffset.x,
                loopObj->getCoords().y + hitboxBoxOffset.y,
                hitboxBoxSize.x,
                hitboxBoxSize.y
        };
#if SHOW_HITBOXES
        DrawRectangleLines(curRect.x, curRect.y, curRect.width, curRect.height, RED);
#endif
        if (CheckCollisionRecs(hitbox, curRect)) {
            for (const auto &listener : m_onHit) {
                listener(*loopObj);
            }
        }
    }
}

mefiddzy::Hitbox::Hitbox(const Vector2 &collisionBoxOffset) : m_collisionBoxOffset(collisionBoxOffset) {}

mefiddzy::Hitbox::Hitbox(mefiddzy::Object &parent) {
    m_collisionBoxSize = {
            static_cast<float>(parent.getTexture().width),
            static_cast<float>(parent.getTexture().height)
    };
}

mefiddzy::Hitbox::Hitbox(const Vector2 &collisionBoxOffset,
                         const Vector2 &collisionBoxSize) : m_collisionBoxSize(collisionBoxSize),
                         m_collisionBoxOffset(collisionBoxOffset) {}



