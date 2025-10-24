#include "object.h"
#include <memory>
#include "raylib.h"
#include "scenes/scene.h"
#include "rce/object_components/object_component.h"
#include <algorithm>
#include "rce/scenes/scene.h"
#include <chrono>

using namespace rce;

const Vector2& Object::getPosition() const {
    return m_position;
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

void Object::setPosition(const Vector2 &mCoords) {
    m_position = mCoords;
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
               float mRotation, float mScale, uint32_t zOrder, const Color &mColor)
        : m_position(mCoords), m_texture(mTexture), m_rotation(mRotation),
          m_scale(mScale), m_color(mColor), m_zOrder(zOrder) {
}

Object::Object(const Object &obj) {
    m_rotation = obj.m_rotation;
    m_scale = obj.m_scale;
    m_color = obj.m_color;
    m_rotation = obj.m_rotation;
    m_texture = obj.m_texture;
    m_position = obj.m_position;
}

Object &Object::operator=(const Object &obj) {
    m_rotation = obj.m_rotation;
    m_scale = obj.m_scale;
    m_color = obj.m_color;
    m_rotation = obj.m_rotation;
    m_texture = obj.m_texture;
    m_position = obj.m_position;

    return *this;
}

auto Object::getComponents() {
    std::vector<std::weak_ptr<IObjectComponent>> components;
    components.reserve(m_components.size());

    for (auto &comp : m_components)
        components.push_back(comp);

    return components;
}

float Object::s_lastFrameTime = 0;

void Object::update() {
    float nowTime;
    {
        using namespace std::chrono;

        auto now = steady_clock::now();
        long long ms = duration_cast<milliseconds>(now.time_since_epoch()).count();

        nowTime = ms / 1000.0;
    }

    if (s_lastFrameTime == 0)
        s_lastFrameTime = nowTime;

    IScene::s_deltaTime = nowTime - s_lastFrameTime;

    s_lastFrameTime = nowTime;

    if (rce::IScene::getLoaded().expired())
        return;

    std::vector<std::weak_ptr<Object>> objectsInScene = rce::IScene::getLoaded().lock()->getLoadedObjects();

    std::sort(objectsInScene.begin(), objectsInScene.end(), [&](const std::weak_ptr<Object> &a, std::weak_ptr<Object> &b){
        if (a.expired() || b.expired())
            return false;

        return a.lock()->getZOrder() < b.lock()->getZOrder();
    });

    for (const std::weak_ptr<Object> &objectWeak : objectsInScene) {
        if (objectWeak.expired())
            continue;

        auto object = objectWeak.lock();

        DrawTextureEx(
                object->m_texture,
                object->m_position,
                object->m_rotation,
                object->m_scale,
                object->m_color
        );

        auto components = object->getComponents();

        for (std::weak_ptr<IObjectComponent> &weakComponent : components) {
            if (weakComponent.expired())
                continue;

            auto component = weakComponent.lock();

            if (component->isEnabled())
                component->onTick(*object);
        }

        object->m_lastScale = object->m_scale;
        object->m_lastRotation = object->m_rotation;
        object->m_lastPosition = object->m_position;
    }
}

void rce::Object::addComponent(std::shared_ptr<IObjectComponent> component) {
    component->onAdd(*this);

    m_components.emplace_back(std::move(component));
}

float rce::Object::getDeltaScale() const {
    return m_scale - m_lastScale;
}

float rce::Object::getDeltaRotation() const {
    return m_rotation - m_lastRotation;
}

Vector2 rce::Object::getDeltaPosition() const {
    return Vector2(
        m_position.x - m_lastPosition.x,
        m_position.y - m_lastPosition.y
    );
}

void Object::setZOrder(uint32_t zOrder) {
    m_zOrder = zOrder;
}

uint32_t Object::getZOrder() const {
    return m_zOrder;
}

