#pragma once

#include <vector>
#include <memory>

namespace mefiddzy {
    class Object;
    namespace scenes {
        class IScene {
        public:
            virtual ~IScene() = default;

            virtual void gameLoop() {}

            virtual void loadScene() {}

            template<typename Scene>
            static void loadScene() {
                static_assert(std::derived_from<Scene, IScene>, "Scene must derive from IScene interface!");

                s_loadedScene = std::make_shared<Scene>();
                s_loadedScene->loadScene();
            }

            static std::weak_ptr<IScene> getLoaded() {
                return s_loadedScene;
            }

        protected:
            std::vector<std::unique_ptr<Object>> m_objects;
            static std::shared_ptr<IScene> s_loadedScene;

        };
    }
}