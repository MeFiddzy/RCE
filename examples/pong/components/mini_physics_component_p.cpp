#include "mini_physics_component_p.h"
#include "raymath.h"
#include <cmath>
#include "../scenes/pong_scene.h"
#include "rce/object_components/hitbox_component.h"
#include "rce/scenes/scene.h"

void rce::examples::MiniPhysicsComponentP::onTick(rce::AbstractObject *parent) {
    parent->setPosition({
        m_velocity.x * IScene::getDeltaTime() * RATIO_DELTA_TIME + parent->getPosition().x,
        m_velocity.y * IScene::getDeltaTime() * RATIO_DELTA_TIME + parent->getPosition().y,
    });
}

void rce::examples::MiniPhysicsComponentP::addVelocity(Vector2 velocity) {
    m_velocity = {
        m_velocity.x + velocity.x,
        m_velocity.y + velocity.y,
    };
}

void rce::examples::MiniPhysicsComponentP::setVelocity(Vector2 velocity) {
    m_velocity = velocity;
}

void rce::examples::MiniPhysicsComponentP::hitPaddle(AbstractObject& other, const HitboxComponent::HitContact& contact ) {
    if (PongScene::getPaddleTag().tagIn(&other)) {
        bounce(contact);

        m_velocity = {
            m_velocity.x + other.getComponent<MiniPhysicsComponentP>().lock()->m_velocity.x / 2,
            m_velocity.y + other.getComponent<MiniPhysicsComponentP>().lock()->m_velocity.y / 2
        };
    }
}

void rce::examples::MiniPhysicsComponentP::bounce(const HitboxComponent::HitContact& contact) {
    m_velocity = {
        -contact.normal.x * 10,
        -contact.normal.y * 10,
    };

    std::cout << contact.normal.x << ", " << contact.normal.y << std::endl;

    if (fabs(m_velocity.x) == fabs(m_velocity.y)) {
        m_velocity.x /= 1.5f;
        m_velocity.y /= 1.5f;
    }
}

void rce::examples::MiniPhysicsComponentP::cancelVelocity() {
    m_velocity = {0, 0};
}

Vector2 rce::examples::MiniPhysicsComponentP::getVelocity() const {
    return m_velocity;
}
