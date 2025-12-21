#include "start_menu_scene.h"

#include "break_the_blocks_scene.h"
#include "rce/object_components/children_component.h"
#include "rce/systems/interactive_objects_system.h"

using namespace rce;
using namespace rce::examples;

void StartMenuScene::onTick() {
    if (m_startGameButton->getPosition().y > GetScreenHeight() - 40) {
        loadScene<BreakTheBlocksScene>(m_slipperyModeSwitch->getValue());
    }

    std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;
}

void StartMenuScene::onLoad() {
    m_backgroundColor = Color(41, 21, 99);

    addSystem(std::make_shared<InteractiveObjectsSystem>());

    m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
        "Slippery\nMode: ",
        40,
        10,
        {750, 1030}
    }));

    m_slipperyModeSwitch = std::dynamic_pointer_cast<RectangleSwitch>(
        m_objects.emplace_back(std::make_shared<RectangleSwitch>(RectangleSwitch{
            {1000, 1050},
            {0, 0},
            0.0f,
            60,
            60,
            GREEN,
            RED
        }))
    );

    m_startGameButton = std::dynamic_pointer_cast<RectangleButton>(
        m_objects.emplace_back(
            std::make_shared<RectangleButton>(RectangleButton{
                {350, 900},
                {0, 0},
                0.0f,
                WHITE,
                600, 100,
                [&](const Vector2& mousePos, InteractiveObject* self) {
                    m_buttonPhysics->addVelocity({0, s_velocityToAddY});
                    m_textPhysics->addVelocity({0, s_velocityToAddY});
                }
            })
        )
    );

    auto startGameText = m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
        "Start Game",
        50,
        10,
        {475, 925},
        BLACK
    }));

    m_breakoidText = std::dynamic_pointer_cast<TextObject>(
        m_objects.emplace_back(
            std::make_shared<TextObject>(TextObject{
                "Breakoid",
                200,
                10,
                {250, 400},
                BLACK
            })
        )
    );

    m_startGameButton->setZOrder(0);
    startGameText->setZOrder(1);

    m_buttonPhysics = std::dynamic_pointer_cast<MiniPhysicsComponent>(
        m_startGameButton->addComponent(std::make_shared<MiniPhysicsComponent>()).lock()
    );

    m_textPhysics = std::dynamic_pointer_cast<MiniPhysicsComponent>(
        startGameText->addComponent(std::make_shared<MiniPhysicsComponent>()).lock()
    );
}