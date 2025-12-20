#pragma once
#include "rce/object_components/hitbox_component.h"
#include "rce/object_components/object_component.h"

namespace rce::examples {
    class MiniPhysicsComponent : public IObjectComponent {
    public:
        void onTick(rce::AbstractObject *parent) override;

        void addVelocity(Vector2 velocity);

        void hitPaddle(AbstractObject& parent, const HitboxComponent::HitContact& contactPoint);

        void bounce(const HitboxComponent::HitContact& contact);

        void cancelVelocity();

    private:
        Vector2 m_velocity{};
    };
}
