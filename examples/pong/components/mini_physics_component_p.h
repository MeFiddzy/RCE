#pragma once
#include "rce/object_components/object_component.h"
#include "rce/object_components/hitbox_component.h"

namespace rce::examples {
    class MiniPhysicsComponentP : public IObjectComponent {
    public:
        void onTick(rce::AbstractObject* parent) override;

        void addVelocity(Vector2 velocity);

        void setVelocity(Vector2 velocity);

        void hitPaddle(AbstractObject& parent, const HitboxComponent::HitContact& contact);

        void bounce(const HitboxComponent::HitContact& contact);

        void cancelVelocity();

        [[nodiscard]] Vector2 getVelocity() const;
    private:
        Vector2 m_velocity{};
    };
}
