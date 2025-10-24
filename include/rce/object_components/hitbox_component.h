#pragma once

#include "object_component.h"
#include "functional"
#include "memory"
#include "raylib.h"

namespace rce {
    class HitboxComponent : public rce::IObjectComponent {
    public:
        class OnHitElem {
        public:
            explicit OnHitElem(std::vector<std::function<void(Object &)>> &onHit, HitboxComponent &hitbox);

            OnHitElem& addListener(const std::function<void(Object&)> &listener);


            HitboxComponent& build();

            OnHitElem(const OnHitElem &&obj) = delete;
        private:
            HitboxComponent &m_hitbox;
            std::vector<std::function<void(Object &)>> &m_onHit;
        };

    public:
        explicit HitboxComponent(const Vector2 &collisionBoxOffset, const Vector2 &collisionBoxSize);
        explicit HitboxComponent(const Vector2 &collisionBoxOffset);
        explicit HitboxComponent(Object &parent);
        HitboxComponent() = default;

        void onTick(rce::Object &self) override;

        OnHitElem onHit();

        [[nodiscard]] Vector2 getCollisionBoxSize() const ;

    private:
        Vector2 m_collisionBoxSize;
        Vector2 m_collisionBoxOffset;
        std::vector<std::function<void(Object&)>> m_onHit;
    };
}