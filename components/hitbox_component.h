#pragma once

#include "component.h"
#include "functional"
#include "memory"
#include "raylib.h"

namespace mefiddzy {
    class HitboxComponent : public mefiddzy::IObjectComponent {
    public:
        class OnHitElem {
        public:
            explicit OnHitElem(std::vector<std::function<void(const Object &)>> &onHit, HitboxComponent &hitbox);

            __forceinline OnHitElem& addListener(const std::function<void(const Object&)> &listener) {
                m_onHit.emplace_back(listener);

                return *this;
            }

            __forceinline HitboxComponent& build() {
                return m_hitbox;
            }

            OnHitElem(const OnHitElem &&obj) = delete;
        private:
            HitboxComponent &m_hitbox;
            std::vector<std::function<void(const Object &)>> &m_onHit;
        };

    public:
        explicit HitboxComponent(const Vector2 &collisionBoxOffset, const Vector2 &collisionBoxSize);
        explicit HitboxComponent(const Vector2 &collisionBoxOffset);
        explicit HitboxComponent(Object &parent);
        HitboxComponent() = default;

        void onTick(mefiddzy::Object &self) override;

        OnHitElem onHit() {
            return OnHitElem(m_onHit, *this);
        }

        Vector2 getCollisionBoxSize() const ;

    private:
        Vector2 m_collisionBoxSize;
        Vector2 m_collisionBoxOffset;
        std::vector<std::function<void(const Object&)>> m_onHit;
    };
}