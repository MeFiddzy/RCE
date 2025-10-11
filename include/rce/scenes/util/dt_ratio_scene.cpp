#include <iostream>
#include "dt_ratio_scene.h"
#include "rce/scenes/scene.h"

void rce::DeltaTimeRatioScene::onTick() {
    m_sum += IScene::getDeltaTime();

    m_sum /= 2;

    std::cout << "Delta time this tick: " << IScene::getDeltaTime() << '\n';
}

void rce::DeltaTimeRatioScene::onUnLoad() {
    std::cout << "Delta time ratio: " << 1 / (m_sum);
}
