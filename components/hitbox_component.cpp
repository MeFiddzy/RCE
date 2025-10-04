#include "hitbox_component.h"
#include "../object.h"
#include "../scenes/scene.h"

#define SHOW_HITBOXES true

using rce::HitboxComponent;

rce::HitboxComponent::OnHitElem::OnHitElem(std::vector<std::function<void(const Object &)>> &onHit,
                                           HitboxComponent &hitbox) : m_onHit(onHit), m_hitbox(hitbox) {}

void rce::HitboxComponent::onTick(rce::Object &parent) {
    Rectangle hitbox = {
            parent.getPosition().x + m_collisionBoxOffset.x,
            parent.getPosition().y + m_collisionBoxOffset.y,
            m_collisionBoxSize.x,
            m_collisionBoxSize.y
    };
#if SHOW_HITBOXES
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, RED);
#endif

    if (rce::scenes::IScene::getLoaded().expired())
        return;

    std::vector<std::weak_ptr<Object>> objectsInScene = rce::scenes::IScene::getLoaded().lock()->getLoadedObjects();

    for (std::weak_ptr<Object> objectWeak : objectsInScene) {
        if (objectWeak.expired())
            continue;

        auto object = objectWeak.lock();

        if (object.get() == &parent || !(object->hasComponent<HitboxComponent>()))
            continue;

        const auto &hitboxObj = object->getComponent<HitboxComponent>();
        const auto &hitboxBoxSize = hitboxObj.m_collisionBoxSize;
        const auto &hitboxBoxOffset = hitboxObj.m_collisionBoxOffset;

        Rectangle curRect = {
                object->getPosition().x + hitboxBoxOffset.x,
                object->getPosition().y + hitboxBoxOffset.y,
                hitboxBoxSize.x,
                hitboxBoxSize.y
        };
#if SHOW_HITBOXES
        DrawRectangleLines(curRect.x, curRect.y, curRect.width, curRect.height, RED);
#endif
        if (CheckCollisionRecs(hitbox, curRect)) {
            for (const auto &listener : m_onHit) {
                listener(*object);
            }
        }
    }
}

rce::HitboxComponent::HitboxComponent(const Vector2 &collisionBoxOffset) : m_collisionBoxOffset(collisionBoxOffset) {}

rce::HitboxComponent::HitboxComponent(rce::Object &parent) {
    m_collisionBoxSize = {
            static_cast<float>(parent.getTexture().width),
            static_cast<float>(parent.getTexture().height)
    };
}

rce::HitboxComponent::HitboxComponent(const Vector2 &collisionBoxOffset,
                                      const Vector2 &collisionBoxSize) : m_collisionBoxSize(collisionBoxSize),
                         m_collisionBoxOffset(collisionBoxOffset) {}



