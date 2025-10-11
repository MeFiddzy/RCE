#include <memory>

#include "scene.h"
#include "../object.h"

using namespace rce;

std::shared_ptr<IScene> IScene::s_loadedScene = nullptr;

float IScene::s_deltaTime = 0;

std::vector<std::weak_ptr<Object>> IScene::getLoadedObjects() {
    std::vector<std::weak_ptr<Object>> objectsCopy;

    for (const auto &object : m_objects) {
        objectsCopy.emplace_back(object);
    }

    return std::move(objectsCopy);
}

float IScene::getDeltaTime() {
    return s_deltaTime;
}
