#include "example_scene"
#include "../object.h"
#include "../components/all.h"
#include <iostream>

using namespace mefiddzy;
using namespace mefiddzy::scenes;

void ExampleScene::gameLoop() {
    if (IsKeyPressed(KEY_F4)) {
        ToggleBorderlessWindowed();
    }

    float addX = 0., addY = 0.;

    if (IsKeyDown(KEY_DOWN)) {
        addY += 6;
    }
    if (IsKeyDown(KEY_UP)) {
        addY += -6;
    }
    if (IsKeyDown(KEY_LEFT)) {
        addX += -6;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        addX += 6;
    }

    Object *player = m_objects[0].get() ;

    player->setPosition({
                                player->getPosition().x + addX,
                                player->getPosition().y + addY
                        });
}

void ExampleScene::loadScene() {
    m_objects.push_back(std::make_unique<Object>(Object{{0, 0},LoadTexture("../resources/player.png")}));
    m_objects.push_back(std::make_unique<Object>(Object{{36, 36},LoadTexture("../resources/player.png")}));
    m_objects.push_back(std::make_unique<Object>(Object{{1000, 1000}}));

    m_objects[0]->addComponent(std::make_unique<HitboxComponent>(
            HitboxComponent({25, 28 }, {453, 445}).onHit().addListener([&](const Object &parent){
                //m_backgroundColor = RED;
                std::cout << "collide\n";
            }).build()
    ));

    m_objects[0]->addComponent(std::make_unique<ChildrenComponent>(ChildrenComponent{}.addChild(m_objects[1])));

    m_objects[1]->addComponent(std::make_unique<HitboxComponent>(HitboxComponent({25, 28 }, {453, 445})));

    m_objects[2]->addComponent(std::make_unique<HitboxComponent>(HitboxComponent{{0, 0}, {10, 10}}));
}
