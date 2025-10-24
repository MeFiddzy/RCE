#include "object_component.h"

using namespace rce;

void IObjectComponent::enable() {
    m_enabled = true;
}

void IObjectComponent::disable() {
    m_enabled = false;
}

void IObjectComponent::toggle() {
    m_enabled = !m_enabled;
}

bool IObjectComponent::isEnabled() const {
    return m_enabled;
}
