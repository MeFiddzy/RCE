#pragma once

#include <memory>
#include <vector>

namespace rce {
    class AbstractObject;
    class IScene;

    class ISystem {
    public:
        virtual ~ISystem() = default;

        ISystem() = default;

        virtual void onSceneTick(std::weak_ptr<IScene> scene) {}

        virtual void onSceneLoad (std::weak_ptr<IScene> scene) {}

        virtual void onSceneUnLoad (std::weak_ptr<IScene> scene) {}

        void enable();
        void disable();
        void toggle();
        [[nodiscard]] bool isEnabled() const;

    protected:
        [[nodiscard]] static std::vector<std::shared_ptr<AbstractObject>>* getObjectsFromScene(IScene* scene);
    private:
        bool m_enabled = true;
    };

   typedef ISystem ISceneComponent;
}
