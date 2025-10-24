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

        void enable();
        void disable();
        void toggle();
        [[nodiscard]] bool isEnabled() const;
    private:
        bool m_enabled = true;
    };

   typedef ISystem ISceneComponent;
}