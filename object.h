#pragma once

#include <vector>
#include <memory>
#include "raylib.h"
#include "components/component.h"
#include <concepts>
#include <exception>

namespace rce{
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

        void addComponent(std::unique_ptr<IObjectComponent> component);

        explicit Object(const Vector2 &mCoords, const Texture2D &mTexture = Texture2D(),
               float mRotation = 0.0f, float mScale = 1.0f, const Color &mColor = WHITE);

        Object(const Object &obj);

        Object() = default;

        ~Object() = default;

        Object& operator=(const Object &obj);

        static void update();

        template<typename Component>
        bool hasComponent() const {
            static_assert(std::derived_from<Component, IObjectComponent>, "Object::hasComponent<Component> | Component doesn't derive from IObjectComponent.");

            for (const auto &component : m_components) {
                if (dynamic_cast<Component*>(component.get()) != nullptr) {
                    return true;
                }
            }
            return false;
        }

        template<typename Component>
        Component& getComponent() {
            static_assert(std::derived_from<Component, IObjectComponent>, "Object::getComponent<Component> | Component doesn't derive from IObjectComponent.");

            for (const auto &component : m_components) {
                if (auto ptr = dynamic_cast<Component*>(component.get())) {
                    return *ptr;
                }
            }

            throw std::runtime_error("Object doesn't have component. Use hasComponent<>() to check!");
        }

        float getDeltaScale() const;

        float getDeltaRotation() const;

        Vector2 getDeltaPosition() const;

    private:
        Vector2 m_position{};
        Texture2D m_texture{};
        float m_rotation;
        float m_scale;
        Color m_color{};

        Vector2 m_lastPosition{};
        float m_lastRotation;
        float m_lastScale;

        std::vector<std::unique_ptr<IObjectComponent>> m_components;
    };
}