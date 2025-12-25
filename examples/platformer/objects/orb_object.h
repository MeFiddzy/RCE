#pragma once
#include "rce/objects/shape/rectangle_object.h"

namespace rce::examples {
    class PhysicsComponent;

    class OrbObject : public RectangleObject {
    public:
        OrbObject(Vector2 position, Vector2 origin, float rotation, Color color, float width, float height, float orbPower = -23.0f);
    private:
        float m_orbPower;
    };
}
