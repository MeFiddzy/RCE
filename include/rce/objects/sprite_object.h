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
    class SpriteObject: public AbstractObject {
    public:
        [[nodiscard]] const Texture2D& getTexture() const;

        void setTexture(const Texture2D &mTexture);

        explicit SpriteObject(const Vector2 &mCoords, const Texture2D &mTexture = Texture2D(),
                              float mRotation = 0.0f, float mScale = 1.0f, uint32_t zOrder = UINT_MAX, const Color &mColor = WHITE);

        SpriteObject(const SpriteObject &obj);

        SpriteObject() = default;

        ~SpriteObject() = default;

        SpriteObject& operator=(const SpriteObject &obj);

        void draw() override;

    private:
        Texture2D m_texture{};
    };
}