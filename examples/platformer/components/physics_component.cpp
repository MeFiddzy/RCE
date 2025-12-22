#include "physics_component.h"

#include "rce/scenes/scene.h"

using namespace rce;
using namespace rce::examples;

const float PhysicsComponent::s_gravity = 13.0f;
const Tag PhysicsComponent::s_groundTag = Tag("PHYSICS:GROUND");

void PhysicsComponent::onHitboxTouch(AbstractObject &other, const HitboxComponent::HitContact &hitContact) {
    if (!s_groundTag.tagIn(&other))
        return;

    m_onGround = true;

    if (hitContact.normal.y == -1) {
        m_normal = -s_gravity;
        m_velocity.y = 0.f;
    }
    else
        m_normal += s_gravity / 40;

    std::cout << m_velocity.x << " " << m_velocity.y << " " << m_normal << std::endl;
}

void PhysicsComponent::onTick(rce::AbstractObject *parent) {
    if (m_normal != -s_gravity && m_normal != 0) {
        m_normal += s_gravity / 40;
    }

    m_onGround = false;

    parent->setPosition({
        parent->getPosition().x + m_velocity.x * RATIO_DELTA_TIME * IScene::getDeltaTime(),
        parent->getPosition().y + (m_velocity.y + (m_affectedByGravity ? (s_gravity + m_normal) : 0)) * RATIO_DELTA_TIME * IScene::getDeltaTime(),
    });
}
