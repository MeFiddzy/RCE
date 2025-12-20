#include "mini_physics_component.h"

#include "raymath.h"
#include "../scenes/break_the_blocks_scene.h"
#include "rce/object_components/hitbox_component.h"
#include "rce/scenes/scene.h"

void rce::examples::MiniPhysicsComponent::onTick(rce::AbstractObject *parent) {
    parent->setPosition({
        m_velocity.x * IScene::getDeltaTime() * RATIO_DELTA_TIME + parent->getPosition().x,
        m_velocity.y * IScene::getDeltaTime() * RATIO_DELTA_TIME + parent->getPosition().y,
    });
}

void rce::examples::MiniPhysicsComponent::addVelocity(Vector2 velocity) {
    m_velocity = {
        m_velocity.x + velocity.x,
        m_velocity.y + velocity.y,
    };
}

void rce::examples::MiniPhysicsComponent::hitPaddle(AbstractObject& other, const HitboxComponent::HitContact& contact ) {
    if (BreakTheBlocksScene::getBounceableTag().tagIn(&other)) {
        bounce(contact);
    }
}

void rce::examples::MiniPhysicsComponent::bounce(const HitboxComponent::HitContact& contact) {
    m_velocity = {
        -contact.normal.x * 10,
        -contact.normal.y * 10,
    };

    if (fabs(m_velocity.x) == fabs(m_velocity.y)) {
        m_velocity.x /= 2;
        m_velocity.y /= 2;
    }

    if (fabs(m_velocity.y) <= 3) {
        m_velocity.y = 3;
    }

    std::cout << m_velocity.x << ", " << m_velocity.y << std::endl;
}

void rce::examples::MiniPhysicsComponent::cancelVelocity() {
    m_velocity = {0, 0};
}
