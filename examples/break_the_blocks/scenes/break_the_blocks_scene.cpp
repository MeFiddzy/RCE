#include "break_the_blocks_scene.h"

#include "you_lost_scene.h"
#include "../components/mini_physics_component.h"
#include "../systems/gen_cubes_system.h"
#include "rce/objects/circle_object.h"
#include "rce/objects/rectangle_object.h"
#include "rce/object_components/hitbox_component.h"
#include "rce/util/tags.h"

using namespace rce::examples;

inline constexpr float MOVEMENT_SPEED = 7.f;
const rce::Tag BreakTheBlocksScene::s_bounceableTag("BREAK_THE_BLOCKS:BOUNCEABLE");

void BreakTheBlocksScene::onTick() {
    if (IsKeyPressed(KEY_R)) {
        loadScene<BreakTheBlocksScene>();
    }

    m_physicsPaddle->cancelVelocity();

    if (IsKeyDown(KEY_LEFT)) {
        m_physicsPaddle->addVelocity({
            -MOVEMENT_SPEED,
            0
        });
    } else if (IsKeyDown(KEY_RIGHT)) {
        m_physicsPaddle->addVelocity({
            MOVEMENT_SPEED,
            0
        });
    }

    if (m_ball->getPosition().x < 0)
        m_physicsBall->bounce(HitboxComponent::HitContact({-.5, 0}, {}));
    if (m_ball->getPosition().x > GetScreenWidth())
        m_physicsBall->bounce(HitboxComponent::HitContact({.5, 0}, {}));
    if (m_ball->getPosition().y < 0)
        m_physicsBall->bounce(HitboxComponent::HitContact({0, -.5}, {}));
    if (m_ball->getPosition().y > GetScreenHeight()) {
        loadScene<YouLostScene>();
        //m_physicsBall->bounce(HitboxComponent::HitContact({0, -1}));
    }
}

void BreakTheBlocksScene::onLoad() {
    m_backgroundColor = Color(41, 21, 99);

    addSystem(std::make_shared<GenCubesSystem>(10, 30));

    m_paddle = std::dynamic_pointer_cast<RectangleObject>(
        m_objects.emplace_back(std::make_shared<rce::RectangleObject>(RectangleObject(
                {325, 1100},
                {0, 0},
                0.0,
                RAYWHITE,
                150,
                20
            )
        )));

    m_ball = std::dynamic_pointer_cast<CircleObject>(
        m_objects.emplace_back(std::make_shared<rce::CircleObject>(
            CircleObject(
                {400, 750},
                WHITE,
                13
            )
        ))
    );

    m_ball->addComponent(std::make_shared<rce::examples::MiniPhysicsComponent>(MiniPhysicsComponent()));
    m_physicsBall = m_ball->getComponent<MiniPhysicsComponent>().lock();

    m_paddle->addComponent(std::make_shared<MiniPhysicsComponent>(MiniPhysicsComponent()));
    m_physicsPaddle = m_paddle->getComponent<MiniPhysicsComponent>().lock();

    m_ball->addComponent(std::make_shared<HitboxComponent>(HitboxComponent(
        {-m_ball->getRadius(), -m_ball->getRadius()},
        {m_ball->getRadius() * 2, m_ball->getRadius() * 2}
    ).onHit().addListener([this](AbstractObject &other, const HitboxComponent::HitContact &contact) {
        m_physicsBall->hitPaddle(other, contact);
    }).build()));

    m_paddle->addComponent(std::make_shared<HitboxComponent>(HitboxComponent(
        {0, 0},
        {m_paddle->getWidth(), m_paddle->getHeight()}
    )));

    m_physicsBall->addVelocity({0, 10});

    s_bounceableTag.addTo(std::dynamic_pointer_cast<AbstractObject>(m_paddle).get());
}
