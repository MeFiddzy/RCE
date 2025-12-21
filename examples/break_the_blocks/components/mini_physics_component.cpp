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
    if (BreakTheBlocksScene::getCubeTag().tagIn(&other)) {
        m_combo++;
        bounce(contact);
    }

    if (BreakTheBlocksScene::getPaddleTag().tagIn(&other)) {
        bounce(contact);

        m_velocity = {
            m_velocity.x + other.getComponent<MiniPhysicsComponent>().lock()->m_velocity.x / 2,
            m_velocity.y,
        };

        m_maxCombo = std::max(m_maxCombo, m_combo);
        //std::cout << "E";
        m_combo = 0;
    }
}

void rce::examples::MiniPhysicsComponent::bounce(const HitboxComponent::HitContact& contact) {
    m_velocity = {
        -contact.normal.x * 10,
        -contact.normal.y * 10,
    };

    if (fabs(m_velocity.x) == fabs(m_velocity.y)) {
        m_velocity.x /= 1.5f;
        m_velocity.y /= 1.5f;
    }

    // if (fabs(m_velocity.y) <= 3) {
    //     m_velocity.y = m_velocity.y >= 0 ? 3 : -3;
    // }

    // std::cout << m_velocity.x << ", " << m_velocity.y << std::endl;
}

void rce::examples::MiniPhysicsComponent::cancelVelocity() {
    m_velocity = {0, 0};
}

Vector2 rce::examples::MiniPhysicsComponent::getVelocity() const {
    return m_velocity;
}
