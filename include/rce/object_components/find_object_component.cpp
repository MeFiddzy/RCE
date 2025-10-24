#include "rce/object_components/find_object_component.h"
#include "rce/object.h"
#include <string>

using namespace rce;

std::unordered_map<std::string, Object*> rce::FindObjectIDComponent::s_ids;

FindObjectIDComponent::FindObjectIDComponent(const std::string &id) {
    m_id = id;
}

void FindObjectIDComponent::onAdd(Object &parent) {
    if (s_ids.contains(m_id))
        return;

    s_ids[m_id] = &parent;
}

Object* FindObjectIDComponent::getObjectByID(const std::string &id) {
    return s_ids[id];
}
