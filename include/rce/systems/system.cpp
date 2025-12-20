#include "system.h"

#include "rce/scenes/scene.h"

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

std::vector<std::shared_ptr<AbstractObject>>* ISystem::getObjectsFromScene(IScene *scene) {
    return &scene->m_objects;
}
