#include "example_scene.h"
#include "../object.h"
#include "../components/all.h"
#include <iostream>

using namespace rce;

void ExampleScene::onTick() {
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

void ExampleScene::onLoad() {
    m_objects.push_back(std::make_shared<Object>(Object{{0, 0},LoadTexture("resources/player.png")}));
    m_objects.push_back(std::make_shared<Object>(Object{{36, 36},LoadTexture("resources/player.png")}));
    m_objects.push_back(std::make_shared<Object>(Object{{1000, 1000}}));

    m_objects[0]->addComponent(std::make_shared<HitboxComponent>(
            HitboxComponent({25, 28 }, {453, 445}).onHit().addListener([&](Object &other){
                if (!other.hasComponent<FindObjectIDComponent>())
                    return;

                if (FindObjectIDComponent::getObjectByID("Test") == &other) {
                    std::cout << "collide\n";
                }
            }).build()
    ));

    m_objects[0]->addComponent(std::make_shared<ChildrenComponent>(ChildrenComponent{}.addChild(m_objects[1])));
    m_objects[0]->setZOrder(0);
    m_objects[1]->setZOrder(1);

    m_objects[1]->addComponent(std::make_shared<HitboxComponent>(HitboxComponent({25, 28 }, {453, 445})));

    m_objects[2]->addComponent(std::make_shared<HitboxComponent>(HitboxComponent{{0, 0}, {10, 10}}));
    m_objects[2]->addComponent(std::make_shared<FindObjectIDComponent>(FindObjectIDComponent{"Test"}));
}
