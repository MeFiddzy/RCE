#include <chrono>
#include <algorithm>
#include "raylib.h"
#include "abstract_object.h"
#include "rce/object_components/object_component.h"
#include "rce/scenes/scene.h"

const Vector2 &rce::AbstractObject::getPosition() const {
    return m_position;
}

void rce::AbstractObject::setPosition(const Vector2 &newPosition) {
    m_position = newPosition;
}

uint32_t rce::AbstractObject::getZOrder() const {
    return m_zOrder;
}

void rce::AbstractObject::setZOrder(uint32_t newZOrder) {
    m_zOrder = newZOrder;
}

std::vector<std::weak_ptr<rce::IObjectComponent>> rce::AbstractObject::getComponents() {
    std::vector<std::weak_ptr<IObjectComponent>> components;
    components.reserve(m_components.size());

    for (auto &comp : m_components)
        components.push_back(comp);

    return components;
}


std::weak_ptr<rce::IObjectComponent> rce::AbstractObject::addComponent(std::shared_ptr<IObjectComponent> component) {
    component->onAdd(this);

    return m_components.emplace_back(std::move(component));
}

float rce::AbstractObject::s_lastFrameTime = 0;

void rce::AbstractObject::update() {
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

    std::vector<std::weak_ptr<AbstractObject>> objectsInScene = rce::IScene::getLoaded().lock()->getLoadedObjects();

    std::sort(objectsInScene.begin(), objectsInScene.end(), [&](const std::weak_ptr<AbstractObject> &a, std::weak_ptr<AbstractObject> &b){
        if (a.expired() || b.expired())
            return false;

        return a.lock()->getZOrder() < b.lock()->getZOrder();
    });

    for (const std::weak_ptr<AbstractObject> &objectWeak : objectsInScene) {
        if (objectWeak.expired())
            continue;

        auto object = objectWeak.lock();

        object->draw();

        auto components = object->getComponents();

        for (std::weak_ptr<IObjectComponent> &weakComponent : components) {
            if (weakComponent.expired())
                continue;

            auto component = weakComponent.lock();

            if (component->isEnabled())
                component->onTick(dynamic_cast<AbstractObject*>(object.get()));
        }

        object->m_lastScale = object->m_scale;
        object->m_lastRotation = object->m_rotation;
        object->m_lastPosition = object->m_position;
    }
}

float rce::AbstractObject::getDeltaScale() const {
    return m_scale - m_lastScale;
}

float rce::AbstractObject::getDeltaRotation() const {
    return m_rotation - m_lastRotation;
}

Vector2 rce::AbstractObject::getDeltaPosition() const {
    return Vector2(
            m_position.x - m_lastPosition.x,
            m_position.y - m_lastPosition.y
    );
}

float rce::AbstractObject::getRotation() const {
    return m_rotation;
}

float rce::AbstractObject::getScale() const {
    return m_scale;
}

const Color& rce::AbstractObject::getColor() const {
    return m_color;
}

bool rce::AbstractObject::hasProperty(const std::string &key) const {
    return m_properties.contains(key);
}

void rce::AbstractObject::removeProperty(const std::string &key) {
    m_properties.erase(key);
}

void rce::AbstractObject::setRotation(float mRotation) {
    m_rotation = mRotation;
}

void rce::AbstractObject::setScale(float mScale) {
    m_scale = mScale;
}

void rce::AbstractObject::setTint(const Color &mColor) {
    m_color = mColor;
}

