#include "ex_scene.h"
#include "../object.h"
#include "../components/hitbox_component.h"
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

   player->setCoords({
        player->getCoords().x + addX,
        player->getCoords().y + addY
   });
}

void ExampleScene::loadScene() {
    m_objects.push_back(std::make_unique<Object>(Object{{0, 0},LoadTexture("../resources/player.png")}));
    m_objects.push_back(std::make_unique<Object>(Object{{36, 36},LoadTexture("../resources/player.png")}));

    m_objects[0]->addComponent(std::make_unique<Hitbox>(
            Hitbox({25, 28 }, {453, 445}).onHit().addListener([](const Object &parent){
                std::cout << "collision\n";
            }).build()
    ));

    m_objects[1]->addComponent(std::make_unique<Hitbox>(Hitbox({25, 28 }, {453, 445})));
}
