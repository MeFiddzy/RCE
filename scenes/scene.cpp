#include <memory>
#include "scene.h"
#include "../object.h"

namespace mefiddzy::scenes {
    std::shared_ptr<IScene> IScene::s_loadedScene = nullptr;

    std::vector<Object*> IScene::getLoadedObjects() {
        std::vector<Object*> objectsCopy;

        for (const auto &object : m_objects) {
            objectsCopy.emplace_back(object.get());
        }

        return std::move(objectsCopy);
    }
}