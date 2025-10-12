#pragma once

#include <memory>

namespace rce {
    class IScene;

    class ISceneComponent {
    public:
        virtual ~ISceneComponent() = default;

        virtual void onSceneTick(std::weak_ptr<IScene> scene) {}

        virtual void onSceneLoad (std::weak_ptr<IScene> scene) {}

        virtual void onSceneUnLoad (std::weak_ptr<IScene> scene) {}
    };
}