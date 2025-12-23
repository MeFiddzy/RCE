#include "hitbox_component.h"
#include "raymath.h"
#include "rce/objects/sprite_object.h"
#include "rce/scenes/scene.h"
#define SHOW_HITBOXES false
using rce::HitboxComponent;

rce::HitboxComponent::OnHitElem::OnHitElem(
    std::vector<std::function<void(AbstractObject &, const HitContact &)> > &onHit,
    HitboxComponent &hitbox) : m_onHit(onHit), m_hitbox(hitbox) {
}

HitboxComponent::OnHitElem &rce::HitboxComponent::OnHitElem::addListener(
    const std::function<void(AbstractObject &, const HitContact &)> &listener) {
    m_onHit.emplace_back(listener);
    return *this;
}

HitboxComponent &rce::HitboxComponent::OnHitElem::build() const { return m_hitbox; }

void rce::HitboxComponent::onTick(rce::AbstractObject *parent) {
    Rectangle hitbox = {
        parent->getPosition().x + m_collisionBoxOffset.x, parent->getPosition().y + m_collisionBoxOffset.y,
        m_collisionBoxSize.x, m_collisionBoxSize.y
    };
#if SHOW_HITBOXES
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, RED);
#endif
    if (rce::IScene::getLoaded().expired())
        return;

    std::vector<std::weak_ptr<AbstractObject> > objectsInScene = rce::IScene::getLoaded().lock()->getLoadedObjects();
    for (const std::weak_ptr<AbstractObject> &objectWeak: objectsInScene) {
        if (objectWeak.expired())
            continue;

        auto object = objectWeak.lock();

        if (object.get() == parent || !(object->hasComponent<HitboxComponent>()))
            continue;

        std::weak_ptr<HitboxComponent> hitboxObjWeak = object->getComponent<HitboxComponent>();

        if (hitboxObjWeak.expired())
            continue;

        std::shared_ptr<HitboxComponent> hitboxObj = hitboxObjWeak.lock();

        const auto &hitboxBoxSize = hitboxObj->m_collisionBoxSize;
        const auto &hitboxBoxOffset = hitboxObj->m_collisionBoxOffset;

        const Rectangle curRect = {
            object->getPosition().x + hitboxBoxOffset.x, object->getPosition().y + hitboxBoxOffset.y, hitboxBoxSize.x,
            hitboxBoxSize.y
        };
        if (CheckCollisionRecs(hitbox, curRect)) {
            HitContact contact{0, 0};

            const Vector2 aCenter = {hitbox.x + hitbox.width * 0.5f, hitbox.y + hitbox.height * 0.5f};
            const Vector2 bCenter = {curRect.x + curRect.width * 0.5f, curRect.y + curRect.height * 0.5f};

            contact.point.x = Clamp(aCenter.x, curRect.x, curRect.x + curRect.width);
            contact.point.y = Clamp(aCenter.y, curRect.y, curRect.y + curRect.height);

            if (contact.point.y < bCenter.y) {
                contact.normal.y = -1;
            }
            else if (contact.point.y > bCenter.y) {
                contact.normal.y = 1;
            }

            if (contact.point.x < bCenter.x) {
                contact.normal.x = 1;
            }
            else if (contact.point.x > bCenter.x) {
                contact.normal.x = -1;
            }

            for (const auto &listener: m_onHit)
                listener(*object, contact);
        }
    }
}

rce::HitboxComponent::HitboxComponent(const Vector2 &collisionBoxOffset) : m_collisionBoxOffset(collisionBoxOffset) {
}

rce::HitboxComponent::HitboxComponent(rce::SpriteObject &parent) {
    m_collisionBoxSize = {
        static_cast<float>(parent.getTexture().width), static_cast<float>(parent.getTexture().height)
    };
}

rce::HitboxComponent::HitboxComponent(const Vector2 &collisionBoxOffset,
                                      const Vector2 &collisionBoxSize) : m_collisionBoxSize(collisionBoxSize),
                                                                         m_collisionBoxOffset(collisionBoxOffset) {
}

Vector2 rce::HitboxComponent::getCollisionBoxSize() const { return m_collisionBoxSize; }
HitboxComponent::OnHitElem rce::HitboxComponent::onHit() { return OnHitElem(m_onHit, *this); }
