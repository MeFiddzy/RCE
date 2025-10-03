#include "object.h"
#include <memory>
#include "raylib.h"
#include "scenes/scene.h"

using mefiddzy::Object;

const Vector2& Object::getCoords() const {
    return m_pos;
}

const Texture2D& Object::getTexture() const {
    return m_texture;
}

float Object::getRotation() const {
    return m_rotation;
}

float Object::getScale() const {
    return m_scale;
}

const Color& Object::getColor() const {
    return m_color;
}

void Object::setCoords(const Vector2 &mCoords) {
    m_pos = mCoords;
}

void Object::setTexture(const Texture2D &mTexture) {
    m_texture = mTexture;
}

void Object::setRotation(float mRotation) {
    m_rotation = mRotation;
}

void Object::setScale(float mScale) {
    m_scale = mScale;
}

void Object::setTint(const Color &mColor) {
    m_color = mColor;
}

Object::Object(const Vector2 &mCoords, const Texture2D &mTexture,
               float mRotation, float mScale, const Color &mColor)
        : m_pos(mCoords), m_texture(mTexture), m_rotation(mRotation),
          m_scale(mScale), m_color(mColor) {
}

Object::Object(const Object &obj) {
    m_rotation = obj.m_rotation;
    m_scale = obj.m_scale;
    m_color = obj.m_color;
    m_rotation = obj.m_rotation;
    m_texture = obj.m_texture;
    m_pos = obj.m_pos;
}

Object &Object::operator=(const Object &obj) {
    m_rotation = obj.m_rotation;
    m_scale = obj.m_scale;
    m_color = obj.m_color;
    m_rotation = obj.m_rotation;
    m_texture = obj.m_texture;
    m_pos = obj.m_pos;

    return *this;
}

void Object::update() {
    if (mefiddzy::scenes::IScene::getLoaded().expired())
        return;

    std::vector<Object*> objectsInScene = mefiddzy::scenes::IScene::getLoaded().lock()->getLoadedObjects();

    for (Object *cur : objectsInScene) {
        DrawTextureEx(
                cur->m_texture,
                cur->m_pos,
                cur->m_rotation,
                cur->m_scale,
                cur->m_color
        );

        for (std::unique_ptr<IObjectComponent> &curComp : cur->m_components) {
            curComp->onTick(*cur);
        }
    }
}

void mefiddzy::Object::addComponent(std::unique_ptr<IObjectComponent> component) {
    m_components.emplace_back(std::move(component));
}


