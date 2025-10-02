#pragma once

#include <vector>
#include <memory>
#include "raylib.h"
#include "components/component.h"

namespace mefiddzy{
    class Object {
    public:
        [[nodiscard]] const Vector2& getCoords() const;

        [[nodiscard]] const Texture2D& getTexture() const;

        [[nodiscard]] float getRotation() const;

        [[nodiscard]] float getScale() const;

        [[nodiscard]] const Color& getColor() const;

        void setCoords(const Vector2 &mCoords);

        void setTexture(const Texture2D &mTexture);

        void setRotation(float mRotation);

        void setScale(float mScale);

        void setTint(const Color &mColor);

        void addComponent(std::unique_ptr<IObjectComponent> component);

        Object(const Vector2 &mCoords, const Texture2D &mTexture,
               float mRotation = 0.0f, float mScale = 1.0f, const Color &mColor = WHITE);

        Object(const Object &obj);

        ~Object() = default;

        Object& operator=(const Object &obj);

        static void update();

        __forceinline static const auto getAllObjects() {
            return s_objects;
        }

    private:
        Vector2 m_pos{};
        Texture2D m_texture{};
        float m_rotation;
        float m_scale;
        Color m_color{};

        std::vector<std::unique_ptr<IObjectComponent>> m_components;

        static std::vector<Object*> s_objects;
    };
}