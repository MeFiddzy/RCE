#include "children_component.h"

using rce::ChildrenComponent;

std::pair<bool, bool>& rce::ChildrenComponent::followPosition() {
    return m_followPosition;
}

bool& rce::ChildrenComponent::followScale() {
    return m_followScale;
}

bool& rce::ChildrenComponent::followRotation() {
    return m_followRotation;
}

void rce::ChildrenComponent::onTick(rce::Object &parent) {
    float deltaRotation = parent.getDeltaRotation();
    float deltaScale = parent.getDeltaScale();
    Vector2 deltaPosition = parent.getDeltaPosition();

    for (const std::weak_ptr<Object> &childWeak : m_children) {
        if (childWeak.expired())
            continue;

        auto child = childWeak.lock();

        if (m_followRotation) {
            child->setRotation(child->getRotation() + deltaRotation);
        }

        if (m_followScale) {
            child->setScale(child->getScale() + deltaScale);
        }

        if (m_followPosition.first) {
            child->setPosition({
                child->getPosition().x + deltaPosition.x,
                child->getPosition().y
            });
        }

        if (m_followPosition.second) {
            child->setPosition({
                child->getPosition().x,
                child->getPosition().y  + deltaPosition.y
            });
        }
    }
}

ChildrenComponent& rce::ChildrenComponent::addChild(std::shared_ptr<Object> &child) {
    m_children.push_back(std::weak_ptr<Object>(child));

    return *this;
}
