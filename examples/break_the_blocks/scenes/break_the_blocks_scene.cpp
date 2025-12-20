#include "break_the_blocks_scene.h"

#include "you_lost_scene.h"
#include "../components/mini_physics_component.h"
#include "rce/objects/circle_object.h"
#include "rce/objects/rectangle_object.h"
#include "rce/object_components/hitbox_component.h"
#include "rce/util/tags.h"

using namespace rce::examples;

inline constexpr float MOVEMENT_SPEED = 5.f;
const rce::Tag BreakTheBlocksScene::s_paddleTag("BREAK_THE_BLOCKS:PADDLE");

void BreakTheBlocksScene::onTick() {
    if (IsKeyDown(KEY_LEFT)) {
        m_paddle->setPosition({
            m_paddle->getPosition().x - MOVEMENT_SPEED * RATIO_DELTA_TIME * IScene::getDeltaTime(),
            m_paddle->getPosition().y
        });
    } else if (IsKeyDown(KEY_RIGHT)) {
        m_paddle->setPosition({
            m_paddle->getPosition().x + MOVEMENT_SPEED * RATIO_DELTA_TIME * IScene::getDeltaTime(),
            m_paddle->getPosition().y
        });
    }

    if (m_ball->getPosition().x < 0)
        m_physicsBall->bounce(HitboxComponent::HitContact({1, 0}));
    if (m_ball->getPosition().x > 800)
        m_physicsBall->bounce(HitboxComponent::HitContact({-1, 0}));
    if (m_ball->getPosition().y < 0)
        m_physicsBall->bounce(HitboxComponent::HitContact({0, 1}));
    if (m_ball->getPosition().y > 600) {
        loadScene<YouLostScene>();
    }
}

void BreakTheBlocksScene::onLoad() {
    m_backgroundColor = Color(41, 21, 99);

    m_paddle = std::dynamic_pointer_cast<RectangleObject>(
        m_objects.emplace_back(std::make_shared<rce::RectangleObject>(RectangleObject(
                {325, 500},
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
                {400, 460},
                WHITE,
                13
            )
        ))
    );

    m_ball->addComponent(std::make_shared<rce::examples::MiniPhysicsComponent>(MiniPhysicsComponent()));
    m_physicsBall = m_ball->getComponent<MiniPhysicsComponent>().lock();

    m_ball->addComponent(std::make_shared<HitboxComponent>(HitboxComponent(
        {-m_ball->getRadius(), -m_ball->getRadius()},
        {m_ball->getRadius() * 2, m_ball->getRadius() * 2}
    ).onHit().addListener([this](AbstractObject &other, const HitboxComponent::HitContact &contact) {
        m_physicsBall->hitPaddle(other, contact);
    }).build()));

    m_paddle->addComponent(std::make_shared<rce::HitboxComponent>(HitboxComponent(
        {0, 0},
        {m_paddle->getWidth(), m_paddle->getHeight()}
    )));

    m_physicsBall->addVelocity({2, 10});

    s_paddleTag.addTo(std::dynamic_pointer_cast<AbstractObject>(m_paddle).get());
}
