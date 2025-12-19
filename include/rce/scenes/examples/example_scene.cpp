#include "example_scene.h"
#include "rce/scenes/scene.h"
#include "rce/objects/sprite_object.h"
#include "rce/object_components/all.h"
#include "rce/objects/text_object.h"
#include <iostream>

using namespace rce::examples;

void ExampleScene::onTick() {
    if (IsKeyPressed(KEY_F4)) {
        ToggleBorderlessWindowed();
    }

    float deltaTime = IScene::getDeltaTime();

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

    m_objects[0]->setPosition({
        m_objects[0]->getPosition().x + (addX * (deltaTime * RATIO_DELTA_TIME)),
        m_objects[0]->getPosition().y + (addY * (deltaTime * RATIO_DELTA_TIME))
    });
}

void ExampleScene::onLoad() {
    auto mainObj = m_objects.emplace_back(std::make_shared<SpriteObject>(SpriteObject{{0, 0}, LoadTexture("resources/player.png")}));
    auto mainChild = m_objects.emplace_back(std::make_shared<SpriteObject>(SpriteObject{{36, 36}, LoadTexture("resources/player.png")}));
    auto collider = m_objects.emplace_back(std::make_shared<SpriteObject>(SpriteObject{{1000, 1000}}));
    auto helloText = m_objects.emplace_back(std::make_shared<TextObject>(TextObject{"Hello", 50, 10,{100, 100}}));

    mainObj->setZOrder(0);

    mainObj->addComponent(std::make_shared<HitboxComponent>(
            HitboxComponent({25, 28 }, {453, 445}).onHit().addListener([&](AbstractObject &other){
                if (!other.hasComponent<FindObjectIDComponent>())
                    return;

                if (FindObjectIDComponent::getObjectByID("Test") == &other) {
                    std::cout << "collide\n";
                }
            }).build()
    ));

    mainObj->addComponent(std::make_shared<ChildrenComponent>(ChildrenComponent{}.addChild(m_objects[1])));
    mainObj->setZOrder(0);
    mainChild->setZOrder(1);

    mainChild->addComponent(std::make_shared<HitboxComponent>(HitboxComponent({25, 28 }, {453, 445})));

    collider->addComponent(std::make_shared<HitboxComponent>(HitboxComponent{{0, 0}, {10, 10}}));
    collider->addComponent(std::make_shared<FindObjectIDComponent>(FindObjectIDComponent{"Test"}));
}
