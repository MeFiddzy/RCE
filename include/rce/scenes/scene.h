#pragma once

#include <vector>
#include <memory>
#include "raylib.h"
#include <set>

/**
 * if you have a movement that works in 60 fps, then it will be the same in every one if you multiply the
 * delta time with this and with the movement speed
**/
#define RATIO_DELTA_TIME 62.0569f

namespace rce {
    class Object;

    class IScene {
    public:
        friend class Object;

        virtual ~IScene() = default;

        IScene() {
            m_backgroundColor = RAYWHITE;
        }

        virtual void onTick() {}

        virtual void onLoad() {}

        virtual void onUnLoad() {}

        std::vector<std::weak_ptr<Object>> getLoadedObjects();

        template<typename Scene, typename ...Args>
        static void loadScene(Args ...args) {
            static_assert(std::derived_from<Scene, IScene>, "Scene must derive from IScene interface!");

            if (s_loadedScene)
                s_loadedScene->onUnLoad();

            s_loadedScene = std::make_shared<Scene>();
            s_loadedScene->onLoad(args...);
        }

        static std::weak_ptr<IScene> getLoaded() {
            return s_loadedScene;
        }

        Color getBackgroundColor() {
            return m_backgroundColor;
        }

        static float getDeltaTime();

    protected:
        std::vector<std::shared_ptr<Object>> m_objects;

        static std::shared_ptr<IScene> s_loadedScene;

        Color m_backgroundColor{};
    private:
        static float s_deltaTime;
    };
}