#include "sprite_object.h"
#include <memory>
#include "raylib.h"
#include "rce/scenes/scene.h"
#include "rce/object_components/object_component.h"
#include <algorithm>
#include "rce/scenes/scene.h"
#include <chrono>

using namespace rce;
using namespace rce;

const Texture2D& SpriteObject::getTexture() const {
    return m_texture;
}

SpriteObject::SpriteObject(const Vector2 &mCoords, const Texture2D &mTexture,
                           float mRotation, float mScale, uint32_t zOrder, const Color &mColor)
        : m_texture(mTexture) {
    m_zOrder = zOrder;
    m_position = mCoords;
    m_rotation = mRotation;
    m_scale = mScale;
    m_color = mColor;
}

SpriteObject::SpriteObject(const SpriteObject &obj)  : AbstractObject(obj) {
    m_rotation = obj.m_rotation;
    m_scale = obj.m_scale;
    m_color = obj.m_color;
    m_rotation = obj.m_rotation;
    m_texture = obj.m_texture;
    m_position = obj.m_position;
}

SpriteObject &SpriteObject::operator=(const SpriteObject &obj) {
    m_rotation = obj.m_rotation;
    m_scale = obj.m_scale;
    m_color = obj.m_color;
    m_rotation = obj.m_rotation;
    m_texture = obj.m_texture;
    m_position = obj.m_position;

    return *this;
}

void SpriteObject::draw() {
    DrawTextureEx(
            m_texture,
            m_position,
            m_rotation,
            m_scale,
            m_color
    );
}


void SpriteObject::setTexture(const Texture2D &mTexture) {
    m_texture = mTexture;
}
