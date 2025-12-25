#pragma once

#include "object_component.h"
#include "functional"
#include "memory"
#include "raylib.h"
#include "raymath.h"

namespace rce {
    class HitboxComponent : public rce::IObjectComponent {
    public:
        struct HitContact {
            Vector2 normal, point;
        };

        class OnHitElem {
        public:
            explicit OnHitElem(std::vector<std::function<void(AbstractObject &, const HitContact&)>> &onHit, HitboxComponent &hitbox);

            OnHitElem& addListener(const std::function<void(AbstractObject&, const HitContact&)> &listener);


            [[nodiscard]] HitboxComponent& build() const;

            OnHitElem(const OnHitElem &&obj) = delete;
        private:
            HitboxComponent &m_hitbox;
            std::vector<std::function<void(AbstractObject &, const HitContact&)>> &m_onHit;
        };

        explicit HitboxComponent(const Vector2 &collisionBoxOffset, const Vector2 &collisionBoxSize);
        explicit HitboxComponent(const Vector2 &collisionBoxOffset);
        explicit HitboxComponent(SpriteObject &parent);
        HitboxComponent() = default;

        void onTick(rce::AbstractObject* self) override;

        OnHitElem onHit();

        [[nodiscard]] Vector2 getCollisionBoxSize() const ;

    private:

        bool SweptAABB(const Vector2& start, const Vector2& end, const Rectangle& box, float radius, HitContact& contact);

        Vector2 m_collisionBoxSize{};
        Vector2 m_collisionBoxOffset{};
        std::vector<std::function<void(AbstractObject&, const HitContact&)>> m_onHit;
    };
}
