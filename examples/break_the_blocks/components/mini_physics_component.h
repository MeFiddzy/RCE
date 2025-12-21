#pragma once
#include "rce/object_components/hitbox_component.h"
#include "rce/object_components/object_component.h"

namespace rce::examples {
    class MiniPhysicsComponent : public IObjectComponent {
    public:
        void onTick(rce::AbstractObject *parent) override;

        void addVelocity(Vector2 velocity);

        void hitPaddle(AbstractObject& parent, const HitboxComponent::HitContact& contact);

        void bounce(const HitboxComponent::HitContact& contact);

        void cancelVelocity();

        [[nodiscard]] Vector2 getVelocity() const;

        [[nodiscard]] int getCombo() const {
            return m_combo;
        }

        [[nodiscard]] int getMaxCombo() const {
            return m_maxCombo;
        }
    private:
        Vector2 m_velocity{};
        int m_maxCombo = 0;
        int m_combo = 0;
    };
}
