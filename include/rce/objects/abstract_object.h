#pragma once

#include <cstdint>
#include <climits>
#include <memory>
#include <iostream>
#include <vector>
#include "raylib.h"

namespace rce {
    class IObjectComponent;

    class AbstractObject {
    public:
        [[nodiscard]] const Vector2& getPosition() const;
        void setPosition(const Vector2& newPosition);

        [[nodiscard]] uint32_t getZOrder() const;
        void setZOrder(uint32_t newZOrder);

        virtual void draw() {}

        template<typename Component>
        [[nodiscard]] bool hasComponent() const {
            static_assert(std::derived_from<Component, IObjectComponent>, "Object::hasComponent<Component> | Component doesn't derive from IObjectComponent.");

            for (const auto &component : m_components) {
                if (dynamic_cast<Component*>(component.get()) != nullptr) {
                    return true;
                }
            }
            return false;
        }

        template<typename Component>
        [[nodiscard]] std::weak_ptr<Component> getComponent() const{
            static_assert(std::derived_from<Component, IObjectComponent>,
                          "Object::getComponent<Component> | Component doesn't derive from IObjectComponent.");

            for (auto &component : m_components) {
                if (auto componentWeak = std::dynamic_pointer_cast<Component>(component)) {
                    return componentWeak;
                }
            }

            std::cerr << "Returned nullptr from rce::Object::getComponent<typename Component>\n"
                      << "Reason: The chosen Component type doesn't exist in the specified rce::Object\n";

            return std::weak_ptr<Component>{};
        }

        std::weak_ptr<IObjectComponent> addComponent(std::shared_ptr<IObjectComponent> component);

        [[nodiscard]]std::vector<std::weak_ptr<IObjectComponent>> getComponents();

        static void update();

        [[nodiscard]] float getDeltaScale() const;

        [[nodiscard]] float getDeltaRotation() const;

        [[nodiscard]] Vector2 getDeltaPosition() const;

        void setRotation(float mRotation);

        void setScale(float mScale);

        void setTint(const Color &mColor);

        [[nodiscard]] float getRotation() const;

        [[nodiscard]] float getScale() const;

        [[nodiscard]] const Color& getColor() const;

    protected:
        Vector2 m_position{};
        float m_rotation{};
        float m_scale{};
        Color m_color{};
        uint32_t m_zOrder{UINT_MAX};

        Vector2 m_lastPosition{};
        float m_lastRotation{};
        float m_lastScale{};

        std::vector<std::shared_ptr<IObjectComponent>> m_components{};

        static float s_lastFrameTime;
    };
}