#include "rce/object_components/find_object_component.h"
#include "rce/objects/sprite_object.h"
#include <string>

using namespace rce;

std::unordered_map<std::string, AbstractObject*> rce::FindObjectIDComponent::s_ids;

FindObjectIDComponent::FindObjectIDComponent(const std::string &id) {
    m_id = id;
}

AbstractObject* FindObjectIDComponent::getObjectByID(const std::string &id) {
    return s_ids[id];
}

void FindObjectIDComponent::onAdd(rce::AbstractObject *parent) {
    if (s_ids.contains(m_id))
        return;

    s_ids[m_id] = parent;
}
