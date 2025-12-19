#pragma once

#include <vector>
#include <memory>
#include "raylib.h"
#include "rce/systems/system.h"
#include <set>
#include <iostream>

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

            if (s_loadedScene) {
                s_loadedScene->onUnLoad();

                for (const auto &component : s_loadedScene->m_systems) {
                    if (component->isEnabled())
                        component->onSceneUnLoad(s_loadedScene);
                }
            }

            s_loadedScene = std::make_shared<Scene>();
            s_loadedScene->onLoad(args...);

            for (const auto &component : s_loadedScene->m_systems) {
                if (component->isEnabled())
                    component->onSceneLoad(s_loadedScene);
            }
        }

        static std::weak_ptr<IScene> getLoaded() {
            return s_loadedScene;
        }

        Color getBackgroundColor() {
            return m_backgroundColor;
        }

        static float getDeltaTime();

        template<typename SceneComponent>
        [[nodiscard]] bool hasSystem() {
            static_assert(std::derived_from<SceneComponent, ISystem>, "Object::hasComponent<Component> | Component doesn't derive from IObjectComponent.");

            for (const auto &component : m_systems) {
                if (dynamic_cast<SceneComponent*>(component.get()) != nullptr) {
                    return true;
                }
            }
            return false;
        }

        template<typename SceneComponent>
        [[nodiscard]] std::weak_ptr<SceneComponent> getSystem() const{
            static_assert(std::derived_from<SceneComponent, ISystem>,
                          "Object::getComponent<Component> | Component doesn't derive from IObjectComponent.");

            for (auto &component : m_systems) {
                if (auto componentWeak = std::dynamic_pointer_cast<SceneComponent>(component)) {
                    return componentWeak;
                }
            }

            std::cerr << "Returned nullptr from rce::Object::getComponent<typename Component>\n"
                      << "Reason: The chosen Component type doesn't exist in the specified rce::Object\n";

            return std::weak_ptr<SceneComponent>{};
        }

        std::weak_ptr<ISystem> addSystem(std::shared_ptr<ISystem> sceneComponent);

        auto getSystems() {
            std::vector<std::weak_ptr<ISystem>> systems;
            systems.reserve(m_systems.size());

            for (auto &comp : m_systems)
                systems.push_back(comp);

            return systems;
        }

    protected:
        std::vector<std::shared_ptr<Object>> m_objects;

        static std::shared_ptr<IScene> s_loadedScene;

        Color m_backgroundColor{};
    private:
        static float s_deltaTime;

        std::vector<std::shared_ptr<ISystem>> m_systems;
    };
}