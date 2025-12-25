#include "orb_object.h"

#include "../components/physics_component.h"
#include "rce/object_components/hitbox_component.h"

using namespace rce::examples;

OrbObject::OrbObject(Vector2 position, Vector2 origin, float rotation, Color color, float width, float height, float orbPower) : RectangleObject(position, origin, rotation, color, width, height) {
    m_orbPower = orbPower;

    addComponent(std::make_shared<HitboxComponent>(HitboxComponent{
        {},
        {width, height}
    }.onHit().addListener([this](AbstractObject& other, const HitboxComponent::HitContact& hitContact) {
        if (!IsKeyPressed(KEY_UP))
            return;

        const std::shared_ptr<PhysicsComponent> physicsComponent = other.getComponent<PhysicsComponent>().lock();
        physicsComponent->resetNormal();
        physicsComponent->setVelocity({0, 0});
        physicsComponent->setVelocity({physicsComponent->getVelocity().x, m_orbPower});
    }).build()));
}