#include "pong_scene.h"

#include <format>
#include <random>

#include "win_scene.h"
#include "../components/mini_physics_component_p.h"
#include "../../../include/rce/objects/shape/circle_object.h"
#include "rce/objects/shape/rectangle_object.h"
#include "rce/object_components/hitbox_component.h"
#include "rce/util/tags.h"

using namespace rce::examples;

inline constexpr float VELOCITY_TO_ADD = 1.f;

const rce::Tag PongScene::s_cubeTag("PONG:CUBE");
const rce::Tag PongScene::s_paddleTag("PONG:PADDLE");

void rce::examples::PongScene::onTick() {
    if (IsKeyPressed(KEY_SLASH)) {
        loadScene<PongScene>(m_settingsData);
    }

    m_physicsPaddleP1->cancelVelocity();

    if (IsKeyDown(KEY_LEFT)) {
        m_physicsPaddleP1->setVelocity({
            (m_settingsData.p1InvertedControls == false ? -1.f : 1.f) * m_settingsData.p1Movement.x,
            (m_settingsData.p1InvertedControls == false ? -1.f : 1.f) * m_settingsData.p1Movement.y,
        });
    } else if (IsKeyDown(KEY_RIGHT)) {
        m_physicsPaddleP1->setVelocity({
            (m_settingsData.p1InvertedControls == false ? 1.f : -1.f) * m_settingsData.p1Movement.x,
            (m_settingsData.p1InvertedControls == false ? 1.f : -1.f) * m_settingsData.p1Movement.y,
        });
    }

    m_physicsPaddleP2->cancelVelocity();

    if (IsKeyDown(KEY_A)) {
        m_physicsPaddleP2->setVelocity({
            (m_settingsData.p2InvertedControls == false ? -1.f : 1.f) * m_settingsData.p2Movement.x,
            (m_settingsData.p2InvertedControls == false ? -1.f : 1.f) * m_settingsData.p2Movement.y,
        });
    } else if (IsKeyDown(KEY_D)) {
        m_physicsPaddleP2->setVelocity({
            (m_settingsData.p2InvertedControls == false ? 1.f : -1.f) * m_settingsData.p2Movement.x,
            (m_settingsData.p2InvertedControls == false ? 1.f : -1.f) * m_settingsData.p2Movement.y,
        });
    }

    if (m_ball->getPosition().x < 0)
        m_physicsBall->bounce(HitboxComponent::HitContact({
            -VELOCITY_TO_ADD,
            (m_physicsBall->getVelocity().y < 0) ? VELOCITY_TO_ADD : -VELOCITY_TO_ADD
        }, {}));
    if (m_ball->getPosition().x > GetScreenWidth())
        m_physicsBall->bounce(HitboxComponent::HitContact({
            VELOCITY_TO_ADD,
            (m_physicsBall->getVelocity().y < 0) ? VELOCITY_TO_ADD : -VELOCITY_TO_ADD
        }, {}));
    if (m_ball->getPosition().y < 0) {
        m_scoreP2++;
        onScoreAdd();
    }
    if (m_ball->getPosition().y > GetScreenHeight()) {
        m_scoreP1++;
        onScoreAdd();
    }
}

void rce::examples::PongScene::onLoad() {
    m_backgroundColor = Color(41, 21, 99);

    m_paddleP1 = std::dynamic_pointer_cast<RectangleObject>(
        m_objects.emplace_back(std::make_shared<rce::RectangleObject>(RectangleObject(
                {750, 200},
                {0, 0},
                0.0,
                RAYWHITE,
                m_settingsData.p1Size.x,
                m_settingsData.p1Size.y
            )
        )));

    m_scoreTextP1 = std::dynamic_pointer_cast<TextObject>(
        m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
            "0",
            70,
            10,
            {80, 200},
            WHITE,
        }))
    );

    m_paddleP2 = std::dynamic_pointer_cast<RectangleObject>(
        m_objects.emplace_back(std::make_shared<rce::RectangleObject>(RectangleObject(
                {750, 1000},
                {0, 0},
                0.0,
                RAYWHITE,
                m_settingsData.p2Size.x,
                m_settingsData.p2Size.y
            )
        )));

    m_scoreTextP2 = std::dynamic_pointer_cast<TextObject>(
        m_objects.emplace_back(std::make_shared<TextObject>(TextObject{
            "0",
            70,
            10,
            {80, 1000},
            WHITE,
        }))
    );

    m_ball = std::dynamic_pointer_cast<CircleObject>(
        m_objects.emplace_back(std::make_shared<rce::CircleObject>(
            CircleObject(
                {825, 600},
                WHITE,
                13
            )
        ))
    );

    m_ball->addComponent(std::make_shared<MiniPhysicsComponentP>(MiniPhysicsComponentP()));
    m_physicsBall = m_ball->getComponent<MiniPhysicsComponentP>().lock();

    m_paddleP1->addComponent(std::make_shared<MiniPhysicsComponentP>(MiniPhysicsComponentP()));
    m_paddleP2->addComponent(std::make_shared<MiniPhysicsComponentP>(MiniPhysicsComponentP()));
    m_physicsPaddleP1 = m_paddleP1->getComponent<MiniPhysicsComponentP>().lock();
    m_physicsPaddleP2 = m_paddleP2->getComponent<MiniPhysicsComponentP>().lock();

    m_ball->addComponent(std::make_shared<HitboxComponent>(HitboxComponent(
        {-m_ball->getRadius(), -m_ball->getRadius()},
        {m_ball->getRadius() * 2, m_ball->getRadius() * 2}
    ).onHit().addListener([this](AbstractObject &other, const HitboxComponent::HitContact &contact) {
        m_physicsBall->hitPaddle(other, contact);
    }).build()));

    m_paddleP1->addComponent(std::make_shared<HitboxComponent>(HitboxComponent(
        {0, 0},
        {m_paddleP1->getWidth(), m_paddleP1->getHeight()}
    )));
    m_paddleP2->addComponent(std::make_shared<HitboxComponent>(HitboxComponent(
        {0, 0},
        {m_paddleP2->getWidth(), m_paddleP2->getHeight()}
    )));

    m_physicsBall->addVelocity({0, 10});

    s_paddleTag.addTo(std::dynamic_pointer_cast<AbstractObject>(m_paddleP1).get());
    s_paddleTag.addTo(std::dynamic_pointer_cast<AbstractObject>(m_paddleP2).get());
}

void PongScene::onScoreAdd() const {
    if (m_scoreP1 >= m_settingsData.winScore) {
        loadScene<WinScene>(1, m_settingsData);
        return;
    }
    if (m_scoreP2 >= m_settingsData.winScore) {
        loadScene<WinScene>(2, m_settingsData);
        return;
    }

    m_physicsBall->setVelocity({0, 0});
    m_ball->setPosition({825, 600});
    m_paddleP2->setPosition({750, 1000});
    m_paddleP1->setPosition({750, 200});

    m_physicsBall->setVelocity({0, 10});

    m_scoreTextP1->setText(std::to_string(m_scoreP1));
    m_scoreTextP2->setText(std::to_string(m_scoreP2));
}
