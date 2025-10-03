#include <memory>
#include "scene.h"

namespace mefiddzy::scenes {
    std::shared_ptr<IScene> IScene::s_loadedScene = nullptr;
}