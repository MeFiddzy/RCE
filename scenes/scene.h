#pragma once

#include <vector>
#include <memory>
#include "raylib.h"

namespace mefiddzy {
    class Object;
    namespace scenes {
        class IScene {
        public:
            virtual ~IScene() = default;

            IScene() {
                m_backgroundColor = RAYWHITE;
            }

            virtual void gameLoop() {}

            virtual void loadScene() {}

            std::vector<std::weak_ptr<Object>> getLoadedObjects();

            template<typename Scene>
            static void loadScene() {
                static_assert(std::derived_from<Scene, IScene>, "Scene must derive from IScene interface!");

                s_loadedScene = std::make_shared<Scene>();
                s_loadedScene->loadScene();
            }

            static std::weak_ptr<IScene> getLoaded() {
                return s_loadedScene;
            }

            Color getBackgroundColor() {
                return m_backgroundColor;
            }

        protected:
            std::vector<std::shared_ptr<Object>> m_objects;
            static std::shared_ptr<IScene> s_loadedScene;

            Color m_backgroundColor{};
        };
    }
}