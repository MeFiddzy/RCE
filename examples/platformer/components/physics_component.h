#pragma once
#include "rce/object_components/hitbox_component.h"
#include "rce/object_components/object_component.h"
#include "rce/util/tags.h"

namespace rce::examples {
    class PhysicsComponent : public IObjectComponent {
    public:
        void onHitboxTouch(AbstractObject& other, const HitboxComponent::HitContact& hitContact);

        PhysicsComponent() = default;

        explicit PhysicsComponent(const bool affectedByGravity) {
            m_affectedByGravity = affectedByGravity;
        }

        void onTick(rce::AbstractObject *parent) override;

        bool isAffectedByGravity() const { return m_affectedByGravity; }

        void setAffectedByGravity(const bool affectedByGravity) { m_affectedByGravity = affectedByGravity; }

        [[nodiscard]] Vector2 getVelocity() const { return m_velocity; }

        void setVelocity(const Vector2 velocity) { m_velocity = velocity; }

        void addVelocity(const Vector2 velocity) { m_velocity = {m_velocity.x + velocity.x, m_velocity.y + velocity.y}; }

        bool isOnGround() const { return m_onGround; }

        static const Tag& getGroundTag() { return s_groundTag; }
    private:
        bool m_affectedByGravity = true;
        Vector2 m_velocity = {};
        float m_normal = 0.f; // OMFG I DONT KNOW PHYSICS :sob: :sob: :sob:
        bool m_onGround = false;

        static const float s_gravity;
        static const Tag s_groundTag;
    };
}
