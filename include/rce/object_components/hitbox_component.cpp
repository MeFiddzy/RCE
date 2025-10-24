#include "hitbox_component.h"
#include "rce/objects/object.h"
#include "rce/scenes/scene.h"

#define SHOW_HITBOXES true

using rce::HitboxComponent;

rce::HitboxComponent::OnHitElem::OnHitElem(std::vector<std::function<void(Object &)>> &onHit,
                                           HitboxComponent &hitbox) : m_onHit(onHit), m_hitbox(hitbox) {}

HitboxComponent::OnHitElem &
rce::HitboxComponent::OnHitElem::addListener(const std::function<void(Object &)> &listener) {
    m_onHit.emplace_back(listener);

    return *this;
}

HitboxComponent &rce::HitboxComponent::OnHitElem::build() {
    return m_hitbox;
}

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

    if (rce::IScene::getLoaded().expired())
        return;

    std::vector<std::weak_ptr<Object>> objectsInScene = rce::IScene::getLoaded().lock()->getLoadedObjects();

    for (const std::weak_ptr<Object> &objectWeak : objectsInScene) {
        if (objectWeak.expired())
            continue;

        auto object = objectWeak.lock();

        if (object.get() == &parent || !(object->hasComponent<HitboxComponent>()))
            continue;

        std::weak_ptr<HitboxComponent> hitboxObjWeak = object->getComponent<HitboxComponent>();

        if (hitboxObjWeak.expired())
            continue;

        std::shared_ptr<HitboxComponent> hitboxObj = hitboxObjWeak.lock();

        const auto &hitboxBoxSize = hitboxObj->m_collisionBoxSize;
        const auto &hitboxBoxOffset = hitboxObj->m_collisionBoxOffset;

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

Vector2 rce::HitboxComponent::getCollisionBoxSize() const {
    return m_collisionBoxSize;
}

HitboxComponent::OnHitElem rce::HitboxComponent::onHit() {
    return OnHitElem(m_onHit, *this);
}



