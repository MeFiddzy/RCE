#include "raylib.h"
#include "abstract_object.h"

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

auto rce::AbstractObject::getComponents() {
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
