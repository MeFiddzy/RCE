#pragma once

#include <vector>
#include <memory>
#include "raylib.h"
#include "rce/object_components/object_component.h"
#include <concepts>
#include <exception>
#include <iostream>

namespace rce {
    class Object {
    public:
        [[nodiscard]] const Vector2& getPosition() const;

        [[nodiscard]] const Texture2D& getTexture() const;

        [[nodiscard]] float getRotation() const;

        [[nodiscard]] float getScale() const;

        [[nodiscard]] const Color& getColor() const;

        void setPosition(const Vector2 &mCoords);

        void setTexture(const Texture2D &mTexture);

        void setRotation(float mRotation);

        void setScale(float mScale);

        void setTint(const Color &mColor);

        void addComponent(std::shared_ptr<IObjectComponent> component);

        explicit Object(const Vector2 &mCoords, const Texture2D &mTexture = Texture2D(),
               float mRotation = 0.0f, float mScale = 1.0f, uint32_t zOrder = UINT_MAX, const Color &mColor = WHITE);

        Object(const Object &obj);

        Object() = default;

        ~Object() = default;

        Object& operator=(const Object &obj);

        static void update();

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

        void setZOrder(uint32_t zOrder);

        [[nodiscard]] uint32_t getZOrder() const;

        [[nodiscard]] float getDeltaScale() const;

        [[nodiscard]] float getDeltaRotation() const;

        [[nodiscard]] Vector2 getDeltaPosition() const;

        [[nodiscard]] auto getComponents();

    private:
        Vector2 m_position{};
        Texture2D m_texture{};
        float m_rotation{};
        float m_scale{};
        Color m_color{};

        uint32_t m_zOrder{UINT_MAX};

        Vector2 m_lastPosition{};
        float m_lastRotation{};
        float m_lastScale{};

        std::vector<std::shared_ptr<IObjectComponent>> m_components;

        static float s_lastFrameTime;
    };
}