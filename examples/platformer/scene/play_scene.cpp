#include "play_scene.h"

#include "../components/physics_component.h"
#include "rce/object_components/hitbox_component.h"

using namespace rce::examples;
using namespace rce;

static constexpr float JUMP_VELOCITY = -11.f;
static constexpr float MOVEMENT_SPEED = 6.f;

void PlayScene::onTick() {
    if (IsKeyDown(KEY_UP) && m_cubePhysics->isOnGround()) {
        m_cubePhysics->setVelocity({m_cubePhysics->getVelocity().x, JUMP_VELOCITY});
    }

    m_cubePhysics->setVelocity({
        0,
        m_cubePhysics->getVelocity().y
    });

    if (IsKeyDown(KEY_LEFT)) {
        m_cubePhysics->addVelocity({-MOVEMENT_SPEED, 0});
    }
    if (IsKeyDown(KEY_RIGHT)) {
        m_cubePhysics->addVelocity({MOVEMENT_SPEED, 0});
    }
}

void PlayScene::onLoad() {
    m_backgroundColor = Color(39, 145, 184, 0);

    m_cube = std::dynamic_pointer_cast<RectangleObject>(
        m_objects.emplace_back(std::make_shared<RectangleObject>(RectangleObject{
            {550, 800},
            {0, 0},
            0.0f,
            ORANGE,
            60,
            60
        }))
    );

    m_ground = std::dynamic_pointer_cast<RectangleObject>(
        m_objects.emplace_back(std::make_shared<RectangleObject>(RectangleObject{
            {0, 1000},
            {0, 0},
            0.0f,
            WHITE,
            1300,
            20
        }))
    );

    m_cubePhysics = std::dynamic_pointer_cast<PhysicsComponent>(
        m_cube->addComponent(std::make_shared<PhysicsComponent>(PhysicsComponent{})).lock()
    );

    m_groundPhysics = std::dynamic_pointer_cast<PhysicsComponent>(
        m_ground->addComponent(std::make_shared<PhysicsComponent>(PhysicsComponent{false})).lock()
    );

    m_cube->addComponent(std::make_shared<HitboxComponent>(HitboxComponent{
        {0., 42.2f},
        {m_cube->getWidth(), m_cube->getHeight()},
    }.onHit().addListener([this](AbstractObject& other, const HitboxComponent::HitContact& hitContact) {
        m_cubePhysics->onHitboxTouch(other, hitContact);
    }).build()));

    m_actualCubeHitbox = std::dynamic_pointer_cast<HitboxComponent>(m_cube->addComponent(std::make_shared<HitboxComponent>(HitboxComponent{
        {0, 0},
        {m_cube->getWidth(), m_cube->getHeight()}
    })).lock());

    m_ground->addComponent(std::make_shared<HitboxComponent>(HitboxComponent{
        {0, 0},
        {m_ground->getWidth(), m_ground->getHeight()},
    }));

    PhysicsComponent::getGroundTag().addTo(m_ground.get());
}
