#pragma once

#include <vector>
#include <memory>
#include "raylib.h"
#include "rce/object_components/object_component.h"
#include "abstract_object.h"
#include <concepts>
#include <exception>
#include <iostream>

namespace rce {
    class Object: public AbstractObject {
    public:
        [[nodiscard]] const Texture2D& getTexture() const;

        [[nodiscard]] float getRotation() const;

        [[nodiscard]] float getScale() const;

        [[nodiscard]] const Color& getColor() const;

        void setTexture(const Texture2D &mTexture);

        void setRotation(float mRotation);

        void setScale(float mScale);

        void setTint(const Color &mColor);

        explicit Object(const Vector2 &mCoords, const Texture2D &mTexture = Texture2D(),
               float mRotation = 0.0f, float mScale = 1.0f, uint32_t zOrder = UINT_MAX, const Color &mColor = WHITE);

        Object(const Object &obj);

        Object() = default;

        ~Object() = default;

        Object& operator=(const Object &obj);

        static void update();

        [[nodiscard]] float getDeltaScale() const;

        [[nodiscard]] float getDeltaRotation() const;

        [[nodiscard]] Vector2 getDeltaPosition() const;

        void draw() override;

    private:
        Texture2D m_texture{};
        float m_rotation{};
        float m_scale{};
        Color m_color{};

        Vector2 m_lastPosition{};
        float m_lastRotation{};
        float m_lastScale{};

        static float s_lastFrameTime;
    };
}