#pragma once

#include <vector>
#include <memory>
#include "raylib.h"
#include <set>

namespace rce {
    class Object;

    class IScene {
    public:
        virtual ~IScene() = default;

        IScene() {
            m_backgroundColor = RAYWHITE;
        }

        virtual void onTick() {}

        virtual void onLoadScene() {}

        std::vector<std::weak_ptr<Object>> getLoadedObjects();

        template<typename Scene>
        static void onLoadScene() {
            static_assert(std::derived_from<Scene, IScene>, "Scene must derive from IScene interface!");

            s_loadedScene = std::make_shared<Scene>();
            s_loadedScene->onLoadScene();
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
    private:

    };
}