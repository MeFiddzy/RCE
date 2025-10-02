#include <iostream>
#include <raylib.h>
#include <memory>

#include "scenes/scene.h"
#include "scenes/ex_scene.h"
#include "components/all.h"
#include "object.h"

int main() {
    InitWindow(640, 480, "TestNeim");
    SetTargetFPS(60);

    using namespace mefiddzy;

    Object player(Vector2{0, 0},LoadTexture("../resources/player.png"));
    Object player2(Vector2{36, 36},LoadTexture("../resources/player.png"));

    player.addComponent(std::make_unique<Hitbox>(
            Hitbox({25, 28 }, {453, 445}).onHit().addListener([](const Object &parent){
                std::cout << "collision\n";
            }).build()
    ));

    player2.addComponent(std::make_unique<Hitbox>(Hitbox({25, 28 }, {453, 445})));

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

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

        player.setCoords({
            player.getCoords().x + addX,
            player.getCoords().y + addY
        });

        Object::update();
        EndDrawing();

    }

    CloseWindow();
}
