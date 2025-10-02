#include "ex_scene.h"
#include "../object.h"
#include "../components/hitbox_component.h"
#include <iostream>

using namespace mefiddzy;
using namespace mefiddzy::scenes;

void ExampleScene::gameLoop() {

}

std::vector<std::unique_ptr<Object>> ExampleScene::getObjectsForLoad() {
    std::vector<std::unique_ptr<Object>> returnVal;

    returnVal.push_back(std::make_unique<Object>(Object{{0, 0},LoadTexture("../resources/player.png")}));
    returnVal.push_back(std::make_unique<Object>(Object{{36, 36},LoadTexture("../resources/player.png")}));

    returnVal[0]->addComponent(std::make_unique<Hitbox>(
            Hitbox({25, 28 }, {453, 445}).onHit().addListener([](const Object &parent){
                std::cout << "collision\n";
            }).build()
    ));

    returnVal[1]->addComponent(std::make_unique<Hitbox>(Hitbox({25, 28 }, {453, 445})));

    return returnVal;
}
