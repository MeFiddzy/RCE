#pragma once
#include "raylib.h"
#include "../../../include/rce/objects/shape/rectangle_object.h"
#include "rce/systems/system.h"

namespace rce::examples {
    class GenCubesSystem : public ISystem {
    public:
        GenCubesSystem(const int cubeNrVer, const int cubeNrHor) : m_cubeNumberHorizontal(cubeNrHor), m_cubeNumberVertical(cubeNrVer) {
            m_cubeLength = GetScreenWidth() / cubeNrHor;
        }

        void onSceneLoad(std::weak_ptr<IScene> scene) override;

        void onSceneTick(std::weak_ptr<IScene> scene) override;

    private:
        float m_cubeLength{};
        int m_cubeNumberVertical;
        int m_cubeNumberHorizontal;

        std::shared_ptr<RectangleObject> m_deleteAtEnd;
    };
}
