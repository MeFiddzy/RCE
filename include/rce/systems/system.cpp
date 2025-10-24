#include "system.h"

using namespace rce;

void ISystem::enable() {
    m_enabled = true;
}

void ISystem::disable() {
    m_enabled = false;
}

void ISystem::toggle() {
    m_enabled = !m_enabled;
}

bool ISystem::isEnabled() const {
    return m_enabled;
}
