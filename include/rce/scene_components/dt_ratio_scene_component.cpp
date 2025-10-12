#include <iostream>
#include "dt_ratio_scene_component.h"
#include "rce/scenes/scene.h"

void rce::DeltaTimeRatioSceneComponent::onSceneUnLoad(std::weak_ptr<IScene> scene) {
    std::cout << "Delta time ratio: " << 1 / (m_sum);
}

void rce::DeltaTimeRatioSceneComponent::onSceneTick(std::weak_ptr<IScene> scene) {
    m_sum += IScene::getDeltaTime();

    m_sum /= 2;

    std::cout << "Delta time this tick: " << IScene::getDeltaTime() << '\n';
}
