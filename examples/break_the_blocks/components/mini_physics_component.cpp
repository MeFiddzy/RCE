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

void rce::examples::MiniPhysicsComponent::hitPaddle(AbstractObject& parent, const HitboxComponent::HitContact& contactPoint ) {
    if (BreakTheBlocksScene::getPaddleTag().tagIn(&parent)) {
        bounce(contactPoint);
    }
}

void rce::examples::MiniPhysicsComponent::bounce(const HitboxComponent::HitContact& contact)
{
    m_velocity = Vector2Reflect(m_velocity, contact.normal);

    std::cout << m_velocity.x << ", " << m_velocity.y << std::endl;
}

/* void rce::examples::MiniPhysicsComponent::bounce(const HitboxComponent::HitContact& contactPoint) {
    cancelVelocity();
    addVelocity({
        contactPoint.normal.x * BOUNCE_POWER,
        contactPoint.normal.y * BOUNCE_POWER,
    });

    std::cout << contactPoint.normal.x << ", " << contactPoint.normal.y << std::endl;
} */

void rce::examples::MiniPhysicsComponent::cancelVelocity() {
    m_velocity = {0, 0};
}
