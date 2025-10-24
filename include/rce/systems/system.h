#pragma once

#include <memory>

namespace rce {
    class IScene;

    class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual void onSceneTick(std::weak_ptr<IScene> scene) {}

        virtual void onSceneLoad (std::weak_ptr<IScene> scene) {}

        virtual void onSceneUnLoad (std::weak_ptr<IScene> scene) {}
    };

   typedef ISystem ISceneComponent;
}