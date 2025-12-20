#include "gen_cubes_system.h"
#include "../lib/util.h"
#include "../scenes/break_the_blocks_scene.h"
#include "rce/objects/rectangle_object.h"
#include "rce/object_components/hitbox_component.h"

using namespace rce;
using namespace rce::examples;

void GenCubesSystem::onSceneLoad(std::weak_ptr<IScene> scene) {
    if (scene.expired())
        return;

    std::vector<std::shared_ptr<AbstractObject>>* sceneObjects = getObjectsFromScene(scene.lock().get());

    auto randEngine = std::mt19937(std::random_device{}());
    auto randDist = std::bernoulli_distribution{0.8};

    float y = 0;
    for (int i = 0; i < m_cubeNumberVertical; i++) {
        float x = 0;
        for (int j = 0; j < m_cubeNumberHorizontal; j++) {
            if (!randDist(randEngine)) {
                x += m_cubeLength;
                continue;
            }

            auto cube = std::make_shared<RectangleObject>(
                RectangleObject{{x, y}, {0,0}, 0.0f, util::randomColor(), m_cubeLength, m_cubeLength}
            );

            cube->addComponent(std::make_shared<HitboxComponent>(
                HitboxComponent{{0,0}, {m_cubeLength, m_cubeLength}}
                    .onHit()
                    .addListener([cube, this](AbstractObject&, const HitboxComponent::HitContact&) {
                        m_deleteAtEnd.emplace_back(cube);
                    })
                    .build()
            ));

            BreakTheBlocksScene::getBounceableTag().addTo(cube.get());

            sceneObjects->emplace_back(cube);
            x += m_cubeLength;
        }
        y += m_cubeLength;
    }
}

void GenCubesSystem::onSceneTick(std::weak_ptr<IScene> scene) {
    std::vector<std::shared_ptr<AbstractObject>>* sceneObjects = getObjectsFromScene(scene.lock().get());

    for (auto cube : m_deleteAtEnd) {
        auto it = std::ranges::find(*sceneObjects, cube);
        if (it != sceneObjects->end())
            sceneObjects->erase(it);
    }
}
